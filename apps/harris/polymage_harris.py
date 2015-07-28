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
