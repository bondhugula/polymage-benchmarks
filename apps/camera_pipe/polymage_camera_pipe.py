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

def camera_pipe():
    # Input Parameters
    R = impipe.Parameter(impipe.Int, "R") # image rows
    C = impipe.Parameter(impipe.Int, "C") # image cols
    kelvin = impipe.Parameter(impipe.Float, "colour_temp") # kelvin
    gamma = impipe.Parameter(impipe.Float, "gamma") # gamma
    contrast = impipe.Parameter(impipe.Float, "contrast") # contrast

    # Image Inputs
    matrix_3200 = impipe.Image(impipe.Float, "matrix_3200", [3, 4])
    matrix_7000 = impipe.Image(impipe.Float, "matrix_7000", [3, 4])
    img = impipe.Image(impipe.Short, "img", [R, C])

    # Vars
    x = impipe.Variable(impipe.Int, "x")
    y = impipe.Variable(impipe.Int, "y")
    c = impipe.Variable(impipe.Int, "c")
    v = impipe.Variable(impipe.Int, "v")

    # shifts in each dimension
    ghostX = 12
    ghostY = 16

    # camera_pipe intervals :
    # bounds for input image
    row = impipe.Interval(impipe.Int, 0, R-1, 1)
    col = impipe.Interval(impipe.Int, 0, C-1, 1)
    # bounds for denoise function
    ghostZone2X = impipe.Interval(impipe.Int, (ghostX-4), (R-24-ghostX+6) - 1, 1)
    ghostZone2Y = impipe.Interval(impipe.Int, (ghostY-4), (C-32-ghostY+6) - 1, 1)
    # ghost zone without any offset(ghost }:))
    ghostZone0X = impipe.Interval(impipe.Int, (ghostX-0), (R-24-ghostX+0) - 1, 1)
    ghostZone0Y = impipe.Interval(impipe.Int, (ghostY-0), (C-32-ghostY+0) - 1, 1)
    # bounds for g_gr, r_r, b_b, g_gb
    halfGhostZone2X = impipe.Interval(impipe.Int, ((ghostX)/2) - 2, ((R-24-ghostX)/2 + 2), 1)
    halfGhostZone2Y = impipe.Interval(impipe.Int, ((ghostY)/2) - 2, ((C-32-ghostY)/2 + 2), 1)
    # bounds for g_r, g_b
    halfGhostZone1X = impipe.Interval(impipe.Int, ((ghostX)/2) - 1, ((R-24-ghostX)/2 + 1), 1)
    halfGhostZone1Y = impipe.Interval(impipe.Int, ((ghostY)/2) - 1, ((C-32-ghostY)/2 + 1), 1)
    # bounds for b_r, b_gr, r_gr, b_gb, r_gb, r_b
    halfGhostZone0X = impipe.Interval(impipe.Int, ((ghostX)/2) - 0, ((R-24-ghostX)/2 + 0), 1)
    halfGhostZone0Y = impipe.Interval(impipe.Int, ((ghostY)/2) - 0, ((C-32-ghostY)/2 + 0), 1)
    # bounds for colour channels    
    rgb = impipe.Interval(impipe.Int, 0, 2, 1)
    grbg = impipe.Interval(impipe.Int, 0, 3, 1)
    # bound for LUT
    lutRange = impipe.Interval(impipe.Int, -32768, 32767, 1)

    #####################################################################################
    # CAMERA PIPELINE

    # 1. Hot Pixel Suppression / Denoising
    XMax = impipe.Max(img(x-2, y), img(x+2, y))
    YMax = impipe.Max(img(x, y-2), img(x, y+2))
    XMin = impipe.Min(img(x-2, y), img(x+2, y))
    YMin = impipe.Min(img(x, y-2), img(x, y+2))
    Max = impipe.Max(XMax, YMax)
    Min = impipe.Min(XMin, YMin)
    clamp = impipe.Min(Max, img(x, y))
    clamp = impipe.Max(Min, clamp)

    denoised = impipe.Function(impipe.Short, "denoised")
    denoised.variableDomain = ([x, y], [ghostZone2X, ghostZone2Y])
    denoised.definition = clamp


    # 2. Deinterleave the Bayer Array
    deinterleaved = impipe.Function(impipe.Short, "deinterleaved")
    deinterleaved.variableDomain = ([c, x, y], [grbg, halfGhostZone2X, halfGhostZone2Y])
    deinterleaved.definition = impipe.Case(impipe.Condition(c, '==', 0), denoised(2*x, 2*y))
    deinterleaved.definition = impipe.Case(impipe.Condition(c, '==', 1), denoised(2*x, 2*y+1))
    deinterleaved.definition = impipe.Case(impipe.Condition(c, '==', 2), denoised(2*x+1, 2*y))
    deinterleaved.definition = impipe.Case(impipe.Condition(c, '==', 3), denoised(2*x+1, 2*y+1))


    # 3. Perform Demosaicing on the Deinterleaved array
    #
    # Halide :
    # "These are the values we already know from the input
    # x_y = the value of channel x at a site in the input of channel y
    # gb refers to green sites in the blue rows
    # gr refers to green sites in the red rows.
    # We'll give more convenient names to the four channels we know"

    g_gr = impipe.Function(impipe.Short, "g_gr")
    g_gr.variableDomain = ([x, y], [halfGhostZone2X, halfGhostZone2Y])
    g_gr.definition = deinterleaved(0, x, y)

    r_r = impipe.Function(impipe.Short, "r_r")
    r_r.variableDomain = ([x, y], [halfGhostZone2X, halfGhostZone2Y])
    r_r.definition = deinterleaved(1, x, y)

    b_b = impipe.Function(impipe.Short, "b_b")
    b_b.variableDomain = ([x, y], [halfGhostZone2X, halfGhostZone2Y])
    b_b.definition = deinterleaved(2, x, y)

    g_gb = impipe.Function(impipe.Short, "g_gb")
    g_gb.variableDomain = ([x, y], [halfGhostZone2X, halfGhostZone2Y])
    g_gb.definition = deinterleaved(3, x, y)

    # Halide :
    # "These are the ones we need to interpolate
    # b_r, g_r, b_gr, r_gr, b_gb, r_gb, r_b, g_b
    #
    # First calculate green at the red and blue sites
    #
    # Try interpolating vertically and horizontally. Also compute
    # differences vertically and horizontally. Use interpolation in
    # whichever direction had the smallest difference."

    def absd(a, b):
        return impipe.Select(impipe.Condition(a, '>', b), a - b, b - a)

    gv_r  =    (g_gb(x-1, y) + g_gb(x, y))/2
    gvd_r = absd(g_gb(x-1, y), g_gb(x, y))
    gh_r  =    (g_gr(x, y+1) + g_gr(x, y))/2
    ghd_r = absd(g_gr(x, y+1), g_gr(x, y))

    g_r = impipe.Function(impipe.Short, "g_r")
    g_r.variableDomain = ([x, y], [halfGhostZone1X, halfGhostZone1Y])
    g_r.definition  = impipe.Select(impipe.Condition(ghd_r, '<', gvd_r), gh_r, gv_r)

    gv_b  =    (g_gr(x+1, y) + g_gr(x, y))/2
    gvd_b = absd(g_gr(x+1, y), g_gr(x, y))
    gh_b  =    (g_gb(x, y-1) + g_gb(x, y))/2
    ghd_b = absd(g_gb(x, y-1), g_gb(x, y))

    g_b = impipe.Function(impipe.Short, "g_b")
    g_b.variableDomain = ([x, y], [halfGhostZone1X, halfGhostZone1Y])
    g_b.definition  = impipe.Select(impipe.Condition(ghd_b, '<', gvd_b), gh_b, gv_b)

    # Halide :
    # "Next interpolate red at gr by first interpolating, then
    # correcting using the error green would have had if we had
    # interpolated it in the same way (i.e. add the second derivative
    # of the green channel at the same place)."

    correction = g_gr(x, y) - (g_r(x, y) + g_r(x, y-1))/2
    r_gr = impipe.Function(impipe.Short, "r_gr")
    r_gr.variableDomain = ([x, y], [halfGhostZone0X, halfGhostZone0Y])
    r_gr.definition = correction + (r_r(x, y-1) + r_r(x, y))/2

    # Halide : "Do the same for other reds and blues at green sites"
    correction = g_gr(x, y) - (g_b(x, y) + g_b(x-1, y))/2
    b_gr = impipe.Function(impipe.Short, "b_gr")
    b_gr.variableDomain = ([x, y], [halfGhostZone0X, halfGhostZone0Y])
    b_gr.definition = correction + (b_b(x, y) + b_b(x-1, y))/2

    correction = g_gb(x, y) - (g_r(x, y) + g_r(x+1, y))/2
    r_gb = impipe.Function(impipe.Short, "r_gb")
    r_gb.variableDomain = ([x, y], [halfGhostZone0X, halfGhostZone0Y])
    r_gb.definition = correction + (r_r(x, y) + r_r(x+1, y))/2

    correction = g_gb(x, y) - (g_b(x, y) + g_b(x, y+1))/2
    b_gb = impipe.Function(impipe.Short, "b_gb")
    b_gb.variableDomain = ([x, y], [halfGhostZone0X, halfGhostZone0Y])
    b_gb.definition = correction + (b_b(x, y) + b_b(x, y+1))/2

    # Halide:
    # "Now interpolate diagonally to get red at blue and blue at
    # red. Hold onto your hats; this gets really fancy. We do the
    # same thing as for interpolating green where we try both
    # directions (in this case the positive and negative diagonals),
    # and use the one with the lowest absolute difference. But we
    # also use the same trick as interpolating red and blue at green
    # sites - we correct our interpolations using the second
    # derivative of green at the same sites."

    correction = g_b(x, y)  - (g_r(x, y) + g_r(x+1, y-1))/2
    rp_b  = correction + (r_r(x, y) + r_r(x+1, y-1))/2
    rpd_b = absd(r_r(x, y), r_r(x+1, y-1))

    correction = g_b(x, y)  - (g_r(x, y-1) + g_r(x+1, y))/2
    rn_b  = correction + (r_r(x, y-1) + r_r(x+1, y))/2
    rnd_b = absd(r_r(x, y-1), r_r(x+1, y))

    r_b = impipe.Function(impipe.Short, "r_b")
    r_b.variableDomain = ([x, y], [halfGhostZone0X, halfGhostZone0Y])
    r_b.definition = impipe.Select(impipe.Condition(rpd_b, '<', rnd_b), rp_b, rn_b)

    # Halide : "Same thing for blue at red"
    correction = g_r(x, y)  - (g_b(x, y) + g_b(x-1, y+1))/2;
    bp_r  = correction + (b_b(x, y) + b_b(x-1, y+1))/2;
    bpd_r = absd(b_b(x, y), b_b(x-1, y+1));

    correction = g_r(x, y)  - (g_b(x, y+1) + g_b(x-1, y))/2;
    bn_r  = correction + (b_b(x, y+1) + b_b(x-1, y))/2;
    bnd_r = absd(b_b(x, y+1), b_b(x-1, y));

    b_r = impipe.Function(impipe.Short, "b_r")
    b_r.variableDomain = ([x, y], [halfGhostZone0X, halfGhostZone0Y])
    b_r.definition = impipe.Select(impipe.Condition(bpd_r, '<', bnd_r), bp_r, bn_r)


    # 4. Interleave the resulting channels
    def interleaveX(a, b, name):
        out = impipe.Function(impipe.Short, name)
        out.variableDomain = ([x, y], [ghostZone0X, ghostZone0Y])
        out.definition = impipe.Select(impipe.Condition((x%2), '==', 0), \
                                                        a(x/2, y), \
                                                        b(x/2, y))
        return out

    def interleaveY(a, b, name):
        out = impipe.Function(impipe.Short, name)
        out.variableDomain = ([x, y], [halfGhostZone0X, ghostZone0Y])
        out.definition = impipe.Select(impipe.Condition((y%2), '==', 0), \
                                                        a(x, y/2), \
                                                        b(x, y/2))
        return out

    red = interleaveX( \
            interleaveY(r_gr, r_r, "redX1"), \
            interleaveY(r_b, r_gb, "redX2"), \
            "red")(x, y)
    green = interleaveX( \
              interleaveY(g_gr, g_r, "greenX1"), \
              interleaveY(g_b, g_gb, "greenX2"), \
            "green")(x, y)
    blue = interleaveX( \
             interleaveY(b_gr, b_r, "blueX1"), \
             interleaveY(b_b, b_gb, "blueX2"), \
           "blue")(x, y)


    # 5. Colour Correction
    #
    # Halide :
    # "Get a color matrix by linearly interpolating between two
    # calibrated matrices using inverse kelvin."

    # reference values:
    # matrix_3200 = [[ 1.6697, -0.2693, -0.4004, -42.4346],
    #                [-0.3576,  1.0615,  1.5949, -37.1158],
    #                [-0.2175, -1.8751,  6.9640, -26.6970]]
    # matrix_7000 = [[ 2.2997, -0.4478,  0.1706, -39.0923],
    #                [-0.3826,  1.5906, -0.2080, -25.4311],
    #                [-0.0888, -0.7344,  2.2832, -20.0826]]

    alpha = (1.0/kelvin - 1.0/3200) / (1.0/7000 - 1.0/3200)

    #def matrix(i, j):
    #    val = (matrix_3200(i, j) * alpha + matrix_7000(i, j) * (1 - alpha))
    #    val = impipe.Cast(impipe.Int, (val * 256.0)) # Halide : "Q8.8 fixed point"
    #    return val

    matrix = impipe.Function(impipe.Int, "matrix")
    matrix.variableDomain = ([x, y], [rgb, grbg])
    val = (matrix_3200(x, y) * alpha + matrix_7000(x, y) * (1 - alpha))
    matrix.definition = impipe.Cast(impipe.Int, val * 256.0)

    r = matrix(0, 3) + matrix(0, 0) * red + matrix(0, 1) * green + matrix(0, 2) * blue;
    g = matrix(1, 3) + matrix(1, 0) * red + matrix(1, 1) * green + matrix(1, 2) * blue;
    b = matrix(2, 3) + matrix(2, 0) * red + matrix(2, 1) * green + matrix(2, 2) * blue;

    corrected = impipe.Function(impipe.Short, "corrected")
    corrected.variableDomain = ([c, x, y], [rgb, ghostZone0X, ghostZone0Y])
    corrected.definition = impipe.Case(impipe.Condition(c, '==', 2), r/256)
    corrected.definition = impipe.Case(impipe.Condition(c, '==', 1), g/256)
    corrected.definition = impipe.Case(impipe.Condition(c, '==', 0), b/256)


    # 6. Apply Curve
    # START
    #
    # Halide :
    # "copied from FCam"

    def lutValue(anything):
        xf = impipe.Cast(impipe.Float, anything/1024.0)

        # clamp
        xf = impipe.Min(1.0, xf)
        xf = impipe.Max(0.0, xf)

        g = impipe.Powf(xf, 1.0/gamma)
        b = 2.0 - impipe.Powf(2.0, contrast/100.0)
        a = 2.0 - 2.0*b
        z = impipe.Select(impipe.Condition(g, '>', 0.5), \
                            1.0 - (a*(1.0-g)*(1.0-g) + b*(1.0-g)), \
                            a*g*g + b*g)
    
        val = impipe.Cast(impipe.UChar, \
                impipe.Min( \
                  impipe.Max(z*256.0, \
                             0.0), \
                  255.0))

        return val

    # compute this beforehand (its a LUT)
    curve = impipe.Function(impipe.UChar, "curveLUT")
    curve.variableDomain = ([v], [lutRange])
    curve.definition = lutValue(v)

    # inLUT = impipe.Condition(corrected(c, x, y), '<=', 65535) & impipe.Condition(corrected(c, x, y), '>=', 0)

    # pick from LUT map
    curved = impipe.Function(impipe.UChar, "process")
    curved.variableDomain = ([c, x, y], [rgb, ghostZone0X, ghostZone0Y])
    # performance measurement :
    # 1. compute on the fly only those out of LUT (positive)
    # curved.definition = impipe.Select(inLUT, \
    #                                   curve(corrected(c, x, y)), \
    #                                   lutValue(corrected(c, x, y))) 
    # 2. compute with exact range [ -2^15 : 2^15 ]
    curved.definition = curve(corrected(c, x, y)) 
    # 3. compute everything on the fly
    # curved.definition = lutValue(corrected(c, x, y)) 

    #####################################################################################
# END
