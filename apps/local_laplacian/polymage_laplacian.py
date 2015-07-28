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

def local_laplacian():
    L = 8 # number of pyramid levels
    levels = 8 # number of intensity levels

    # Input Parameters
    R = impipe.Parameter(impipe.Int, "R") # image rows
    C = impipe.Parameter(impipe.Int, "C") # image cols
    alpha = impipe.Parameter(impipe.Float, "alpha") # alpha
    beta = impipe.Parameter(impipe.Float, "beta") # beta
    # Images
    img_colour = impipe.Image(impipe.UShort, "img_colour", [3, R+4, C+4])

    # Vars
    x = impipe.Variable(impipe.Int, "x") # for rows
    y = impipe.Variable(impipe.Int, "y") # for cols
    c = impipe.Variable(impipe.Int, "c") # for colours
    r = impipe.Variable(impipe.Int, "r") # for remap LUT
    k = impipe.Variable(impipe.Int, "k") # for LUT levels

    # Intervals
    rgb = impipe.Interval(impipe.Int, 0, 2, 1) # for colours
    rows = impipe.Interval(impipe.Int, 0, R+3, 1)
    cols = impipe.Interval(impipe.Int, 0, C+3, 1)
    rows2 = impipe.Interval(impipe.Int, 0, R-1, 1)
    cols2 = impipe.Interval(impipe.Int, 0, C-1, 1)
    lutLev = impipe.Interval(impipe.Int, 0, levels-1, 1) # for LUT levels
    rLut = impipe.Interval(impipe.Int, -256*(levels-1), 256*(levels-1)-1, 1) # for LUT


    #####################################################################################

    # DOWNSAMPLE
    def pyrDown(f, l, kl, name):
        # decrement factor
        decFactor = 1 << l
        # original factor
        orgFactor = 1 << (l-1)

        # domain (downsampled)
        decRowr = impipe.Interval(impipe.Int, 0, (R/decFactor)+3, 1)
        decColr = impipe.Interval(impipe.Int, 0, (C/decFactor)+3, 1)
        # domain (original)
        colr = impipe.Interval(impipe.Int, 0, (C/orgFactor)+3, 1)

        # downsample in 'x' dimesnion (using a [1 3 3 1]' filter)

        # body case
        condx = impipe.Condition(x, '>=', 2) & \
                impipe.Condition(x, '<=', (R/decFactor)+1) & \
                impipe.Condition(y, '>=', 2) & \
                impipe.Condition(y, '<=', (C/orgFactor)+1)
        # boundary cases
        condxLeft   = impipe.Condition(y, '<=', 1)
        condxRight  = impipe.Condition(y, '>=', (C/orgFactor)+2)
        condxTop    = impipe.Condition(x, '<=', 1)
        condxBottom = impipe.Condition(x, '>=', (R/decFactor)+2)
        
        downx = impipe.Function(impipe.Float, "Dx_" + name + "_L" + str(l))
        # if the function does not have dimension 'k'
        if kl:
            downx.variableDomain = ([x, y], [decRowr, colr])
            downx.definition = impipe.Case(condx, (f(2*(x-1)-1, y) +
                                                   f(2*(x-1)  , y) * 3.0 +
                                                   f(2*(x-1)+1, y) * 3.0 +
                                                   f(2*(x-1)+2, y)
                                                  ) * 0.125)
        # if the function has dimension 'k'
        else:
            downx.variableDomain = ([k, x, y], [lutLev, decRowr, colr])
            downx.definition = impipe.Case(condx, (f(k, 2*(x-1)-1, y) +
                                                   f(k, 2*(x-1)  , y) * 3.0 +
                                                   f(k, 2*(x-1)+1, y) * 3.0 +
                                                   f(k, 2*(x-1)+2, y)
                                                  ) * 0.125)
        #fi

        # set the boundaries to zero
        downx.definition = impipe.Case(condxLeft, 0)
        downx.definition = impipe.Case(condxRight, 0)
        downx.definition = impipe.Case(condxBottom, 0)
        downx.definition = impipe.Case(condxTop, 0)


        # downsample in 'y' dimension (using a [1 3 3 1] filter)

        condy = impipe.Condition(x, '>=', 2) & \
                impipe.Condition(x, '<=', (R/decFactor)+1) & \
                impipe.Condition(y, '>=', 2) & \
                impipe.Condition(y, '<=', (C/decFactor)+1)
        condyLeft   = impipe.Condition(y, '<=', 1)
        condyRight  = impipe.Condition(y, '>=', (C/decFactor)+2)
        condyTop    = impipe.Condition(x, '<=', 1)
        condyBottom = impipe.Condition(x, '>=', (R/decFactor)+2)

        downy = impipe.Function(impipe.Float, "D_" + name + "_L" + str(l))
        if kl:
            downy.variableDomain = ([x, y], [decRowr, decColr])
            downy.definition = impipe.Case(condy, (downx(x, 2*(y-1)-1) +
                                                   downx(x, 2*(y-1)  ) * 3.0 + 
                                                   downx(x, 2*(y-1)+1) * 3.0 +
                                                   downx(x, 2*(y-1)+2)
                                                  ) * 0.125)
        else:
            downy.variableDomain = ([k, x, y], [lutLev, decRowr, decColr])
            downy.definition = impipe.Case(condy, (downx(k, x, 2*(y-1)-1) +
                                                   downx(k, x, 2*(y-1)  ) * 3.0 +
                                                   downx(k, x, 2*(y-1)+1) * 3.0 +
                                                   downx(k, x, 2*(y-1)+2)
                                                  ) * 0.125)
        #fi

        downy.definition = impipe.Case(condyLeft, 0)
        downy.definition = impipe.Case(condyRight, 0)
        downy.definition = impipe.Case(condyBottom, 0)
        downy.definition = impipe.Case(condyTop, 0)

        return downy


    # UPSAMPLE
    def pyrUp(f, l, kl, name):
        decFactor = 1 << l+1
        orgFactor = 1 << l

        # domain (original)
        decColr = impipe.Interval(impipe.Int, 0, (C/decFactor)+3, 1)

        # domain (upsampled)
        colr = impipe.Interval(impipe.Int, 0, (C/orgFactor)+3, 1)
        rowr = impipe.Interval(impipe.Int, 0, (R/orgFactor)+3, 1)

        # upsample in 'x' dimension

        condx = impipe.Condition(x, '>=', 2) & \
                impipe.Condition(x, '<=', (R/orgFactor)+1) & \
                impipe.Condition(y, '>=', 2) & \
                impipe.Condition(y, '<=', (C/decFactor)+1)
        condxLeft   = impipe.Condition(y, '<=', 1)
        condxRight  = impipe.Condition(y, '>=', (C/decFactor)+2)
        condxTop    = impipe.Condition(x, '<=', 1)
        condxBottom = impipe.Condition(x, '>=', (R/orgFactor)+2)

        upx = impipe.Function(impipe.Float, "Ux_" + name + "_L" + str(l))
        if kl:
            evenXexpr = 0.25 * f(x/2  , y) + 
                        0.75 * f(x/2+1, y)
            oddXexpr =  0.25 * f(x/2+2, y) + 
                        0.75 * f(x/2+1, y)
            upx.variableDomain = ([x, y], [rowr, decColr])
        else:
            evenXexpr = 0.25 * f(k, x/2  , y) +
                        0.75 * f(k, x/2+1, y)
            oddXexpr =  0.25 * f(k, x/2+2, y) + 
                        0.75 * f(k, x/2+1, y)
            upx.variableDomain = ([k, x, y], [lutLev, rowr, decColr])
        #fi
        upXexpr = impipe.Select(impipe.Condition(x%2, "==", 0),
                                evenXexpr,
                                oddXexpr)

        upx.definition = impipe.Case(condx, upXexpr)

        upx.definition = impipe.Case(condxLeft, 0)
        upx.definition = impipe.Case(condxRight, 0)
        upx.definition = impipe.Case(condxBottom, 0)
        upx.definition = impipe.Case(condxTop, 0)


        # upsample in 'y' dimension

        condy = impipe.Condition(x, '>=', 2) & \
                impipe.Condition(x, '<=', (R/orgFactor)+1) & \
                impipe.Condition(y, '>=', 2) & \
                impipe.Condition(y, '<=', (C/orgFactor)+1)
        condyLeft   = impipe.Condition(y, '<=', 1)
        condyRight  = impipe.Condition(y, '>=', (C/orgFactor)+2)
        condyTop    = impipe.Condition(x, '<=', 1)
        condyBottom = impipe.Condition(x, '>=', (R/orgFactor)+2)

        upy = impipe.Function(impipe.Float, "U_" + name + "_L" + str(l))
        if kl:
            evenYexpr = 0.25 * upx(x, y/2    ) +
                        0.75 * upx(x, y/2 + 1)
            oddYexpr =  0.25 * upx(x, y/2 + 2) +
                        0.75 * upx(x, y/2 + 1)
            upy.variableDomain = ([x, y], [rowr, colr])
        else:
            evenYexpr = 0.25 * upx(k, x, y/2    ) +
                        0.75 * upx(k, x, y/2 + 1)
            oddYexpr =  0.25 * upx(k, x, y/2 + 2) +
                        0.75 * upx(k, x, y/2 + 1)
            upy.variableDomain = ([k, x, y], [lutLev, rowr, colr])
        #fi
        upYexpr = impipe.Select(impipe.Condition(y%2, "==", 0),
                                evenYexpr,
                                oddYexpr)

        upy.definition = impipe.Case(condy, upYexpr)

        upy.definition = impipe.Case(condyLeft, 0)
        upy.definition = impipe.Case(condyRight, 0)
        upy.definition = impipe.Case(condyBottom, 0)
        upy.definition = impipe.Case(condyTop, 0)

        return upy


    #####################################################################################
    # LOCAL LAPLACIAN :

    # 0. Convert to Gray
    img = impipe.Function(impipe.Float, "img")
    img.variableDomain = ([x, y], [rows, cols])
    img.definition = (
                     0.299 * img_colour(2, x, y) +\
                     0.587 * img_colour(1, x, y) +\
                     0.114 * img_colour(0, x, y)
                     ) / 65535.0 #255.0


    # 1. Make Gaussian Pyramid of the input.
    inGPyramid = {}
    inGPyramid[0] = img
    for l in range(1, L):
        inGPyramid[l] = pyrDown(inGPyramid[l-1], l, True, "inGPyramid")


    # 2. Remapping function
    '''
    # not as a LUT
    def remap(thing):
        fx = impipe.Cast(impipe.Float, thing) / 256.0
        val = alpha * fx * impipe.Exp( -fx*fx / 2.0 )
        return val
    '''

    # as a LUT
    fx = impipe.Cast(impipe.Float, r) / 256.0
    val = alpha * fx * 
          impipe.Exp( -fx*fx / 2.0 ) # pow(e, _)

    remap = impipe.Function(impipe.Float, "remapLUT")
    remap.variableDomain = ([r], [rLut])
    remap.definition = val


    # 3. Make the processed Gaussian Pyramid
    gPyramid = {}
    # Do a lookup into a lut with 256 entires per intensity level
    iLevel = k * (1.0 / (levels-1))
    idx = img(x, y) * impipe.Cast(impipe.Float, (levels-1)*256.0)
    # clamp idx
    idx = impipe.Min(
            impipe.Max(
              impipe.Cast(impipe.Int, idx),
              0),
            (levels-1)*256)

    gPyramid[0] = impipe.Function(impipe.Float, "gPyramid_L0")
    gPyramid[0].variableDomain = ([k, x, y], [lutLev, rows, cols])
    gPyramid[0].definition = beta * ( img(x, y) - iLevel ) + 
                             iLevel + 
                             remap(idx - 256*k)
    for l in range(1, L):
        gPyramid[l] = pyrDown(gPyramid[l-1], l, False, "gPyramid")


    # 4. Get the laplacian of processed Gaussian Pyramid
    lPyramid = {}
    # level: L-1
    lPyramid[L-1] = gPyramid[L-1]
    # level: everything else
    for l in range(L-2, -1, -1):
        rowr = impipe.Interval(impipe.Int, 0, (R/(1<<l))+3)
        colr = impipe.Interval(impipe.Int, 0, (C/(1<<l))+3)

        lPyramid[l] = impipe.Function(impipe.Float, "lPyramid" + "_L"  + str(l))
        lPyramid[l].variableDomain = ([k, x, y], [lutLev, rowr, colr])
        lPyramid[l].definition = gPyramid[l](k, x, y) - 
                                 pyrUp(gPyramid[l+1], l, False, "gPyramid")(k, x, y)


    # 5. Make the Laplacian Pyramid for the output
    outLPyramid = {}
    for l in range(0, L):
        # Split input pyramid value into integer(LUT index) and floating(weight) parts
        lev = inGPyramid[l](x, y) * impipe.Cast(impipe.Float, (levels-1))
        # LUT index - clamped:[0, levels-2]
        li = impipe.Min( impipe.Max( impipe.Cast(impipe.Int, lev), 0), levels-2 )
        # weight
        lf = lev - li

        rowr = impipe.Interval(impipe.Int, 0, (R/(1<<l))+3)
        colr = impipe.Interval(impipe.Int, 0, (C/(1<<l))+3)

        # Linearly interpolate between the nearest processed pyramid levels
        outLPyramid[l] = impipe.Function(impipe.Float, "outLPyramid_L" + str(l))
        outLPyramid[l].variableDomain = ([x, y], [rowr, colr])
        outLPyramid[l].definition = lPyramid[l](li  , x, y) * (1.0 - lf) + 
                                    lPyramid[l](li+1, x, y) * lf


    # 6. Make the Gaussian pyramid of the output
    outGPyramid = {}
    outGPyramid[L-1] = outLPyramid[L-1]
    for l in range(L-2, -1, -1):
        if l == 0:
            outGPyramid[l] = impipe.Function(impipe.Float, "result_ref_gray")
            outGPyramid[l].variableDomain = ([x, y], [rows, cols])
        else:
            rowr = impipe.Interval(impipe.Int, 0, (R/(1<<l))+3)
            colr = impipe.Interval(impipe.Int, 0, (C/(1<<l))+3)
            outGPyramid[l] = impipe.Function(impipe.Float, "outGPyramid_L" + str(l))
            outGPyramid[l].variableDomain = ([x, y], [rowr, colr])
        #fi
        outGPyramid[l].definition = pyrUp(outGPyramid[l+1], l, True, "outGPyramid")(x, y) + 
                                    outLPyramid[l](x, y)

    result_ref_gray = outGPyramid[0]


    # 7. 
    # Halide :
    # "Reintroduce color (Connelly: use eps to avoid scaling up noise
    # w/ apollo3.png input)"
    eps = 0.01
    colourMap = outGPyramid[0](x+2, y+2) * 
                ((img_colour(c, x+2, y+2)/65535.0) + eps) / (img(x+2, y+2) + eps)
    colourMap = impipe.Min( impipe.Max( colourMap, 0.0 ), 1.0 ) # clamp
    colourMap = impipe.Cast( impipe.UShort, colourMap * 65535.0)

    colour = impipe.Function(impipe.UShort, "laplacian")
    colour.variableDomain = ([c, x, y], [rgb, rows2, cols2])
    colour.definition = colourMap

    result_ref_colour = colour

    #####################################################################################
# END
