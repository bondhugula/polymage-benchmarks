# PolyMage Specification
# ======================

def unsharp_mask():

    # Params
    R = impipe.Parameter(impipe.Int, "R")
    C = impipe.Parameter(impipe.Int, "C")
    threshold = impipe.Parameter(impipe.Float, "threshold")
    weight = impipe.Parameter(impipe.Float, "weight")

    # Vars
    x = impipe.Variable(impipe.Int, "x")
    y = impipe.Variable(impipe.Int, "y")
    c = impipe.Variable(impipe.Int, "c")

    # Input Image
    img = impipe.Image(impipe.Float, "img", [3, R+4, C+4])

    # Intervals
    cr = impipe.Interval(impipe.Int, 0, 2, 1)
    xrow = impipe.Interval(impipe.Int, 2, R+1, 1)
    xcol = impipe.Interval(impipe.Int, 0, C+3, 1)
    yrow = impipe.Interval(impipe.Int, 2, R+1, 1)
    ycol = impipe.Interval(impipe.Int, 2, C+1, 1)

    #####################################################################################
    # UNSHARP MASK

    blurx = impipe.Function(impipe.Float, "blurx")
    blurx.variableDomain = ([c, x, y], [cr, xrow, xcol])
    blurx.definition = ( img(c, x-2, y) \
                       + img(c, x-1, y) * 4.0 \
                       + img(c, x  , y) * 6.0 \
                       + img(c, x+1, y) * 4.0 \
                       + img(c, x+2, y) ) * 0.0625

    blury = impipe.Function(impipe.Float, "blury")
    blury.variableDomain = ([c, x, y], [cr, yrow, ycol])
    blury.definition = ( blurx(c, x, y-2) \
                       + blurx(c, x, y-1) * 4.0 \
                       + blurx(c, x, y  ) * 6.0 \
                       + blurx(c, x, y+1) * 4.0 \
                       + blurx(c, x, y+2) ) * 0.0625

    sharpen = impipe.Function(impipe.Float, "sharpen")
    sharpen.variableDomain = ([c, x, y], [cr, yrow, ycol])
    sharpen.definition = img(c, x, y)   * ( 1 + weight ) \
                       - blury(c, x, y) * (     weight )

    masked = impipe.Function(impipe.Float, "mask")
    masked.variableDomain = ([c, x, y], [cr, yrow, ycol])
    masked.definition = impipe.Select( impipe.Condition( \
                                         impipe.Abs(img(c, x, y) - blury(c, x, y)), \
                                         '<', \
                                         threshold), \
                                       img(c, x, y), \
                                       sharpen(c, x, y) )

    #####################################################################################
# END
