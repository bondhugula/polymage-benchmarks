'''
  Copyright (c) 2015 Indian Institute of Science
  All rights reserved.
  
  Written and provided by:
  Ravi Teja Mullapudi, Vinay Vasista, Uday Bondhugula
  Dept of Computer Science and Automation
  Indian Institute of Science
  Bangalore 560012 
  India
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  
  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  
  3. Neither the name of the Indian Institute of Science nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.
  
  THIS MATERIAL IS PROVIDED BY Ravi Teja Mullapudi, Vinay Vasista, and Uday
  Bondhugula, Indian Institute of Science ''AS IS'' AND ANY EXPRESS OR IMPLIED
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
  EVENT SHALL Ravi Teja Mullapudi, Vinay Vasista, CSA Indian Institute of Science
  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
'''

# PolyMage Specification
# ======================

def interpolate():
    L = 10 # number of pyramid levels

    # Params
    R = impipe.Parameter(impipe.Int, "R") # image rows
    C = impipe.Parameter(impipe.Int, "C") # image cols

    # Vars
    x = impipe.Variable(impipe.Int, "x")
    y = impipe.Variable(impipe.Int, "y")
    c = impipe.Variable(impipe.Int, "c")

    # Input Image
    img = impipe.Image(impipe.Float, "img", [4, R+2, C+2])

    # Intervals
    rgba = impipe.Interval(impipe.Int, 0, 3, 1) # colour with alpha channel
    rgb = impipe.Interval(impipe.Int, 0, 2, 1) # colour channels
    row = impipe.Interval(impipe.Int, 0, R+1, 1)
    col = impipe.Interval(impipe.Int, 0, C+1, 1)
    row2 = impipe.Interval(impipe.Int, 0, R-1, 1)
    col2 = impipe.Interval(impipe.Int, 0, C-1, 1)

    #####################################################################################

    # DOWNSAMPLE
    def pyrDown(f, l, name):
        # decrement factor
        decFactor = 1 << l
        # original factor
        orgFactor = 1 << (l-1)

        # domain (downsampled)
        decRowr = impipe.Interval(impipe.Int, 0, (R/decFactor)+1, 1)
        decColr = impipe.Interval(impipe.Int, 0, (C/decFactor)+1, 1)
        # domain (original)
        colr = impipe.Interval(impipe.Int, 0, (C/orgFactor)+1, 1)

        # downsample in 'x' dimension (using [1 2 1]' filter)

        # body case
        condx = impipe.Condition(x, '>=', 1) & \
                impipe.Condition(x, '<=', (R/decFactor)) & \
                impipe.Condition(y, '>=', 1) & \
                impipe.Condition(y, '<=', (C/orgFactor))
        # boundary cases
        condxLeft   = impipe.Condition(y, '<=', 0)
        condxRight  = impipe.Condition(y, '>=', (C/orgFactor)+1)
        condxTop    = impipe.Condition(x, '<=', 0)
        condxBottom = impipe.Condition(x, '>=', (R/decFactor)+1)

        downx = impipe.Function(impipe.Float, "Dx_" + str(l) + "_" + name)
        downx.variableDomain = ([c, x, y], [rgba, decRowr, colr])
        downx.definition = impipe.Case(condx, (f(c, 2*x-2, y) + \
                                               f(c, 2*x-1, y) * 2.0 + \
                                               f(c, 2*x  , y) \
                                              ) * 0.25)
        # set the boundaries to zero
        downx.definition = impipe.Case(condxLeft, 0)
        downx.definition = impipe.Case(condxRight, 0)
        downx.definition = impipe.Case(condxBottom, 0)
        downx.definition = impipe.Case(condxTop, 0)
    
        # Please refer to 'local_laplacian' app to check how to set
        # boundary conditions if necessary

        # downsample in 'y' dimension (using [1 2 1] filter)

        condy = impipe.Condition(x, '>=', 1) & \
                impipe.Condition(x, '<=', (R/decFactor)) & \
                impipe.Condition(y, '>=', 1) & \
                impipe.Condition(y, '<=', (C/decFactor))
        condyLeft   = impipe.Condition(y, '<=', 0)
        condyRight  = impipe.Condition(y, '>=', (C/decFactor)+1)
        condyTop    = impipe.Condition(x, '<=', 0)
        condyBottom = impipe.Condition(x, '>=', (R/decFactor)+1)

        downy = impipe.Function(impipe.Float, "D_" + str(l) + "_" + name)
        downy.variableDomain = ([c, x, y], [rgba, decRowr, decColr])
        downy.definition = impipe.Case(condy, (downx(c, x, 2*y-2) + \
                                               downx(c, x, 2*y-1) * 2.0 + \
                                               downx(c, x, 2*y  )
                                              ) * 0.25)
        downy.definition = impipe.Case(condyLeft, 0)
        downy.definition = impipe.Case(condyRight, 0)
        downy.definition = impipe.Case(condyBottom, 0)
        downy.definition = impipe.Case(condyTop, 0)


        return downy

    # UPSAMPLE & INTERPOLATE
    def pyrUp_Xpolate(f, d, l, name):
        decFactor = 1 << l+1
        orgFactor = 1 << l

        # domain (original)
        decRowr = impipe.Interval(impipe.Int, 0, (R/decFactor)+1, 1)
        decColr = impipe.Interval(impipe.Int, 0, (C/decFactor)+1, 1)

        # domain (upsampled)
        colr = impipe.Interval(impipe.Int, 0, (C/orgFactor)+1, 1)
        rowr = impipe.Interval(impipe.Int, 0, (R/orgFactor)+1, 1)

        # upsample in 'x' dimension
        condx = impipe.Condition(x, '>=', 1) & \
                impipe.Condition(x, '<=', (R/orgFactor)) & \
                impipe.Condition(y, '>=', 1) & \
                impipe.Condition(y, '<=', (C/decFactor))
        condxLeft   = impipe.Condition(y, '<=', 0)
        condxRight  = impipe.Condition(y, '>=', (C/decFactor)+1)
        condxTop    = impipe.Condition(x, '<=', 0)
        condxBottom = impipe.Condition(x, '>=', (R/orgFactor)+1)

        upx = impipe.Function(impipe.Float, "Ux_" + name)
        upx.variableDomain = ([c, x, y], [rgba, rowr, decColr])
        upx.definition = impipe.Case(condx, (f(c, (x+1)/2, y) + \
                                             f(c, (x+2)/2, y) \
                                            ) / 2.0)
        upx.definition = impipe.Case(condxLeft, 0)
        upx.definition = impipe.Case(condxRight, 0)
        upx.definition = impipe.Case(condxBottom, 0)
        upx.definition = impipe.Case(condxTop, 0)

        # upsample in 'y' dimension and interpolate
        condy = impipe.Condition(x, '>=', 1) & \
                impipe.Condition(x, '<=', (R/orgFactor)) & \
                impipe.Condition(y, '>=', 1) & \
                impipe.Condition(y, '<=', (C/orgFactor))
        condyLeft   = impipe.Condition(y, '<=', 0)
        condyRight  = impipe.Condition(y, '>=', (C/orgFactor)+1)
        condyTop    = impipe.Condition(x, '<=', 0)
        condyBottom = impipe.Condition(x, '>=', (R/orgFactor)+1)

        upy = (upx(c, x, (y+1)/2) + \
               upx(c, x, (y+2)/2)) / 2.0

        interpolate = impipe.Function(impipe.Float, name)
        interpolate.variableDomain = ([c, x, y], [rgba, rowr, colr])
        interpolate.definition = impipe.Case( condy, d(c, x, y) + \
                                                     (1.0 - d(3, x, y)) * upy )
        interpolate.definition = impipe.Case(condyLeft, 0)
        interpolate.definition = impipe.Case(condyRight, 0)
        interpolate.definition = impipe.Case(condyBottom, 0)
        interpolate.definition = impipe.Case(condyTop, 0)

        return interpolate


    #####################################################################################
    # MULTISCALE INTERPOLATION

    # 1.
    downsampled = {}
    # level : 0
    downsampled[0] = impipe.Function(impipe.Float, "downsampled_L0")
    downsampled[0].variableDomain = ([c, x, y], [rgba, row, col])
    downsampled[0].definition = img(c, x, y) * img(3, x, y)
    # level : everything else
    for l in range(1, L):
        downsampled[l] = pyrDown(downsampled[l-1], l, "downsampled")


    # 2.
    interpolated = {}
    # level : L-1
    interpolated[L-1] = downsampled[L-1]
    # level : everything else
    for l in range(L-2, -1, -1):
        interpolated[l] = pyrUp_Xpolate(interpolated[l+1], downsampled[l], l, "interpolated_L" + str(l))


    # 3. Normalize
    normalized = impipe.Function(impipe.Float, "interpolate")
    normalized.variableDomain = ([c, x, y], [rgb, row2, col2])
    normalized.definition = interpolated[0](c, x+1, y+1) / interpolated[0](3, x+1, y+1)

    #####################################################################################
# END
