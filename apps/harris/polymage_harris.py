# PolyMage Specification
# ======================

def harris_corner():
    # Params
    R = impipe.Parameter(impipe.Int, "R")
    C = impipe.Parameter(impipe.Int, "C")

    # Vars
    x = impipe.Variable(impipe.Int, "x")
    y = impipe.Variable(impipe.Int, "y")

    # Intervals
    row = impipe.Interval(impipe.Int, 0, R+1, 1)
    col = impipe.Interval(impipe.Int, 0, C+1, 1)

    # Input Image
    img = impipe.Image(impipe.Float, "img", [R+2, C+2])

    cond = impipe.Condition(x, '>=', 1) & \
           impipe.Condition(x, '<=', R) & \
           impipe.Condition(y, '>=', 1) & \
           impipe.Condition(y, '<=', C)

    # reduced size domain
    condRed = impipe.Condition(x, '>=', 2) & \
              impipe.Condition(x, '<=', R-1) & \
              impipe.Condition(y, '>=', 2) & \
              impipe.Condition(y, '<=', C-1)

    #####################################################################################
    # HARRIS CORNER DETECTION

    Iy = impipe.Function(impipe.Float, "Iy")
    Iy.variableDomain = ([x, y], [row, col])
    Iy.definition = impipe.Case(cond, (img(x-1, y-1)*(-1) + img(x-1, y+1)*(1) + \
                                       img(x  , y-1)*(-2) + img(x  , y+1)*(2) + \
                                       img(x+1, y-1)*(-1) + img(x+1, y+1)*(1)) \
                                       / 12.0)

    Ix = impipe.Function(impipe.Float, "Ix")
    Ix.variableDomain = ([x, y], [row, col])
    Ix.definition = impipe.Case(cond, (img(x-1, y-1)*(-1) + img(x-1, y  )*(-2) + img(x-1, y+1)*(-1) +\
                                       img(x+1, y-1)*( 1) + img(x+1, y  )*( 2) + img(x+1, y+1)*( 1))\
                                       / 12.0)

    Ixx = impipe.Function(impipe.Float, "Ixx")
    Ixx.variableDomain = ([x, y], [row, col])
    Ixx.definition = impipe.Case(cond, Ix(x, y) * Ix(x, y))

    Iyy = impipe.Function(impipe.Float, "Iyy")
    Iyy.variableDomain = ([x, y], [row, col])
    Iyy.definition = impipe.Case(cond, Iy(x, y) * Iy(x, y))

    Ixy = impipe.Function(impipe.Float, "Ixy")
    Ixy.variableDomain = ([x, y], [row, col])
    Ixy.definition = impipe.Case(cond, Ix(x, y) * Iy(x, y))

    Sxx = impipe.Function(impipe.Float, "Sxx")
    Sxx.variableDomain = ([x, y], [row, col])
    Sxx.definition = impipe.Case(condRed, Ixx(x-1, y-1) + Ixx(x-1, y) + Ixx(x-1, y+1) +\
                                          Ixx(x  , y-1) + Ixx(x  , y) + Ixx(x  , y+1) +\
                                          Ixx(x+1, y-1) + Ixx(x+1, y) + Ixx(x+1, y+1))

    Syy = impipe.Function(impipe.Float, "Syy")
    Syy.variableDomain = ([x, y], [row, col])
    Syy.definition = impipe.Case(condRed, Iyy(x-1, y-1) + Iyy(x-1, y) + Iyy(x-1, y+1) +\
                                          Iyy(x  , y-1) + Iyy(x  , y) + Iyy(x  , y+1) +\
                                          Iyy(x+1, y-1) + Iyy(x+1, y) + Iyy(x+1, y+1))

    Sxy = impipe.Function(impipe.Float, "Sxy")
    Sxy.variableDomain = ([x, y], [row, col])
    Sxy.definition = impipe.Case(condRed, Ixy(x-1, y-1) + Ixy(x-1, y) + Ixy(x-1, y+1) +\
                                          Ixy(x  , y-1) + Ixy(x  , y) + Ixy(x  , y+1) +\
                                          Ixy(x+1, y-1) + Ixy(x+1, y) + Ixy(x+1, y+1))

    det = impipe.Function(impipe.Float, "det")
    det.variableDomain = ([x, y], [row, col])
    det.definition = impipe.Case(condRed, Sxx(x, y) * Syy(x, y) - Sxy(x, y) * Sxy(x, y))

    trace = impipe.Function(impipe.Float, "trace")
    trace.variableDomain = ([x, y], [row, col])
    trace.definition = impipe.Case(condRed, Sxx(x, y) + Syy(x, y))

    harris = impipe.Function(impipe.Float, "harris")
    harris.variableDomain = ([x, y], [row, col])
    harris.definition = impipe.Case(condRed, det(x, y) - 0.04 * trace(x, y) * trace(x, y))

    #####################################################################################
# END
