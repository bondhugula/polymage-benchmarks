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

def pyramid_blending():
    L = 4 # number of pyramid levels

    # Params
    R = impipe.Parameter(impipe.Int, "R") # image rows
    C = impipe.Parameter(impipe.Int, "C") # image cols

    # Vars
    x = impipe.Variable(impipe.Int, "x")
    y = impipe.Variable(impipe.Int, "y")
    c = impipe.Variable(impipe.Int, "c")

    # Input Images
    img1 = impipe.Image(impipe.Float, "img1", [3, R+4, C+4])
    img2 = impipe.Image(impipe.Float, "img2", [3, R+4, C+4])
    mask = impipe.Image(impipe.Float, "mask", [R+4, C+4])

    # Intervals
    cr = impipe.Interval(impipe.Int, 0, 2, 1) # colour channels

    #####################################################################################

    # DOWNSAMPLE
    def pyrDown(f, l, colour, name):
        # decrement factor
        decFactor = 1 << l
        # original factor
        orgFactor = 1 << (l-1)

        # domain (downsampled)
        decRowr = impipe.Interval(impipe.Int, 0, (R/decFactor) + 3, 1)
        decColr = impipe.Interval(impipe.Int, 0, (C/decFactor) + 3, 1)
        # domain (original)
        colr = impipe.Interval(impipe.Int, 0, (C/orgFactor)+3, 1)

        # downsample in 'x' dimension (using [1 4 6 4 1]' filter)

        # body case
        condx = impipe.Condition(x, '>=', 2) & \
                impipe.Condition(x, '<=', (R/decFactor) + 1) & \
                impipe.Condition(y, '>=', 2) & \
                impipe.Condition(y, '<=', (C/orgFactor) + 1)

        downx = impipe.Function(impipe.Float, "Dx_" + str(l) + "_" + name)
        # if the image is coloured
        if colour:
            downx.variableDomain = ([c, x, y], [cr, decRowr, colr])
            downx.definition = impipe.Case(condx, (f(c, 2*(x-1)-2, y) + \
                                                   f(c, 2*(x-1)-1, y) * 4.0 + \
                                                   f(c, 2*(x-1)  , y) * 6.0 + \
                                                   f(c, 2*(x-1)+1, y) * 4.0 + \
                                                   f(c, 2*(x-1)+2, y) \
                                                  ) * 0.0625)
        # if grayscale image
        else:
            downx.variableDomain = ([x, y], [decRowr, colr])
            downx.definition = impipe.Case(condx, (f(2*(x-1)-2, y) + \
                                                   f(2*(x-1)-1, y) * 4.0 + \
                                                   f(2*(x-1)  , y) * 6.0 + \
                                                   f(2*(x-1)+1, y) * 4.0 + \
                                                   f(2*(x-1)+2, y) \
                                                  ) * 0.0625)
        #fi

        # Please refer to 'local_laplacian' app to check how to set
        # boundary conditions if necessary

        # downsample in 'y' dimension (using [1 4 6 4 1] filter)

        condy = impipe.Condition(x, '>=', 2) & \
                impipe.Condition(x, '<=', (R/decFactor) + 1) & \
                impipe.Condition(y, '>=', 2) & \
                impipe.Condition(y, '<=', (C/decFactor) + 1)

        downy = impipe.Function(impipe.Float, "Dy_" + str(l) + "_" + name)
        if color:
            downy.variableDomain = ([c, x, y], [cr, decRowr, decColr])
            downy.definition = impipe.Case(condy, (downx(c, x, 2*(y-1)-2) + \
                                                   downx(c, x, 2*(y-1)-1) * 4.0 + \
                                                   downx(c, x, 2*(y-1)  ) * 6.0 + \
                                                   downx(c, x, 2*(y-1)+1) * 4.0 + \
                                                   downx(c, x, 2*(y-1)+2) \
                                                  ) * 0.0625)
        else:
            downy.variableDomain = ([x, y], [decRowr, decColr])
            downy.definition = impipe.Case(condy, (downx(x, 2*(y-1)-2) + \
                                                   downx(x, 2*(y-1)-1) * 4.0 + \
                                                   downx(x, 2*(y-1)  ) * 6.0 + \
                                                   downx(x, 2*(y-1)+1) * 4.0 + \
                                                   downx(x, 2*(y-1)+2) \
                                                  ) * 0.0625)
        #fi

        return downy


    # UPSAMPLE
    def pyrUp(f, l, name):
        decFactor = 1 << l+1
        orgFactor = 1 << l

        # domain (original)
        decColr = impipe.Interval(impipe.Int, 0, (C/decFactor) + 3, 1)

        # domain (upsampled)
        colr = impipe.Interval(impipe.Int, 0, (C/orgFactor)+3, 1)
        rowr = impipe.Interval(impipe.Int, 0, (R/orgFactor)+3, 1)

        # upsample in 'x' dimension
        condx = impipe.Condition(x, '>=', 2) & \
                impipe.Condition(x, '<=', (R/orgFactor) + 1) & \
                impipe.Condition(y, '>=', 2) & \
                impipe.Condition(y, '<=', (C/decFactor) + 1)

        evenxexpr =  (f(c, x/2  , y) + \
                      f(c, x/2+1, y) * 6.0 + \
                      f(c, x/2+2, y) \
                     ) * 0.125 
        oddxexpr  =  (f(c, (x-1)/2+1, y) * 4.0 + \
                      f(c, (x+1)/2+1, y) * 4.0 \
                     ) * 0.125
        upxexpr = impipe.Select(impipe.Condition(x%2, "==", 0), \
                                evenxexpr, \
                                oddxexpr) 

        upx = impipe.Function(impipe.Float, "Ux_" + str(l) + "_" + name)
        upx.variableDomain = ([c, x, y], [cr, rowr, decColr])
        upx.definition = impipe.Case(condx, upxexpr)

        # upsample in 'y' dimension
        condy = impipe.Condition(x, '>=', 2) & \
                impipe.Condition(x, '<=', (R/orgFactor) + 1) & \
                impipe.Condition(y, '>=', 2) & \
                impipe.Condition(y, '<=', (C/orgFactor) + 1)

        evenyexpr =  (upx(c, x, y/2  ) + \
                      upx(c, x, y/2+1) * 6.0 + \
                      upx(c, x, y/2+2) \
                     ) * 0.125
        oddyexpr  =  (upx(c, x, (y-1)/2+1) * 4.0 + \
                      upx(c, x, (y+1)/2+1) * 4.0 \
                     ) * 0.125
        upyexpr = impipe.Select(impipe.Condition(y%2, "==", 0), \
                                evenyexpr, \
                                oddyexpr)

        upy = impipe.Function(impipe.Float, "Uy_" + str(l) + "_" + name)
        upy.variableDomain = ([c, x, y], [cr, rowr, colr])
        upy.definition = impipe.Case(condy, upyexpr)
        return upy


    def laplace(f1, f2, l, name):
        colr = impipe.Interval(impipe.Int, 0, (C/(1<<l))+3, 1)
        rowr = impipe.Interval(impipe.Int, 0, (R/(1<<l))+3, 1)

        lapl = impipe.Function(impipe.Float, name+"_"+str(l))
        lapl.variableDomain = ([c, x, y], [cr, rowr, colr])
        lapl.definition = f2(c, x, y) - f1(c, x, y)

        return lapl

    def blend(lap1, lap2, m, l):
        rowr = impipe.Interval(impipe.Int, 0, (R/(1<<l)) + 3, 1)
        colr = impipe.Interval(impipe.Int, 0, (C/(1<<l)) + 3, 1)

        reslap = impipe.Function(impipe.Float, "Res_" + str(l))
        reslap.variableDomain = ([c, x, y], [cr, rowr, colr])
        reslap.definition = lap1(c, x, y) * (    m(x, y)) + \
                            lap2(c, x, y) * (1 - m(x, y))

        return reslap
 
    def collapse(f1, f2, l, name):
        colr = impipe.Interval(impipe.Int, 0, (C/(1<<l))+3, 1)
        rowr = impipe.Interval(impipe.Int, 0, (R/(1<<l))+3, 1)

        coll = impipe.Function(impipe.Float, name+"_"+str(l))
        coll.variableDomain = ([c, x, y], [cr, rowr, colr])
        coll.definition = f1(c, x, y) + f2(c, x, y)

        return coll


    #####################################################################################
    # PYRAMID BLENDING
 
    # 1. Gaussian pyramid construction
    GaussImg1 = {}
    GaussImg2 = {}
    GaussMask = {}
    GaussImg1[0] = img1
    GaussImg2[0] = img2
    GaussMask[0] = mask
    for l in xrange(1, L):
        GaussImg1[l] = pyrDown(GaussImg1[l-1], l, True, "img1")
        GaussImg2[l] = pyrDown(GaussImg2[l-1], l, True, "img2")
        GaussMask[l] = pyrDown(GaussMask[l-1], l, False, "mask")


    # 2. Laplacian pyramid construction
    LaplImg1 = {}
    LaplImg2 = {}
    for l in xrange(0, L-1):
        LaplImg1[l] = laplace(pyrUp(GaussImg1[l+1], l, "img1"), GaussImg1[l], l, "lapl1")
        LaplImg2[l] = laplace(pyrUp(GaussImg2[l+1], l, "img2"), GaussImg2[l], l, "lapl2")
    LaplImg1[L-1] = GaussImg1[L-1]
    LaplImg2[L-1] = GaussImg2[L-1]


    # 3. Blend the images using mask
    resLapl = {}
    for l in xrange(0, L):
        resLapl[l] = blend(LaplImg1[l], LaplImg2[l], GaussMask[l], l)


    # 4. Collapsing pyramid of blended image samples
    outPyr = {}
    outPyr[L-1] = resLapl[L-1]
    for l in xrange(L-2, 0, -1):
        outPyr[l] = collapse(pyrUp(outPyr[l+1], l, "coll"), resLapl[l], l, "coll")
    outPyr[0] = collapse(pyrUp(outPyr[1], 0, "blend"), resLapl[0], 0, "blend")

    #####################################################################################
# END
