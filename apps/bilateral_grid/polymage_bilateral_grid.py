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

def bilateral_grid():
    # Params
    rows = impipe.Parameter(impipe.Int, "rows")
    cols = impipe.Parameter(impipe.Int, "cols")

    # Vars
    x = impipe.Variable(impipe.Int, "x")
    y = impipe.Variable(impipe.Int, "y")
    z = impipe.Variable(impipe.Int, "z")
    c = impipe.Variable(impipe.Int, "c")

    # Intervals
    rowr = impipe.Interval(impipe.Int, 0, rows-1, 1)
    colr = impipe.Interval(impipe.Int, 0, cols-1, 1)

    # Input Images
    img = impipe.Image(impipe.Float, "input", [rows, cols])


    #####################################################################################
    # BILATERAL GRID

    # sigma_s is hardcoded to 8 and sigma_r is hardcoded to 0.1 
    # Bilateral grid
    invSigma_r = 10
    sigma_s = 8

    gridrowr = impipe.Interval(impipe.Int, 0, rows/sigma_s + 3, 1)
    gridcolr = impipe.Interval(impipe.Int, 0, cols/sigma_s + 3, 1)
    gridintr = impipe.Interval(impipe.Int, 0, invSigma_r + 3, 1)

    cr = impipe.Interval(impipe.Int, 0, 1)
    cd = impipe.Interval(impipe.Int, 0, 0)

    # Accumulation
    grid = impipe.Accumulator(impipe.Float, "grid")
    grid.variableDomain  = ([c, x, y, z], [cr, gridrowr, gridcolr, gridintr])
    grid.reductionDomain = ([x, y], [rowr, colr])
    intaccess = impipe.Cast(impipe.Int, (img(x, y) * invSigma_r))
    grid.definition = impipe.Accumulate(grid(0, 2 + (x/sigma_s), 2 + (y/sigma_s), 2 + intaccess), \
                                        img(x, y), impipe.Op.Sum)
    grid.definition = impipe.Accumulate(grid(1, 2 + (x/sigma_s), 2 + (y/sigma_s), 2 + intaccess), \
                                        1, impipe.Op.Sum)
    grid.default = 0

    cond = impipe.Condition(x, '>=', 2) & \
           impipe.Condition(x, '<=', rows/sigma_s + 1) & \
           impipe.Condition(y, '>=', 2) & \
           impipe.Condition(y, '<=', cols/sigma_s + 1) & \
           impipe.Condition(z, '>=', 2) & \
           impipe.Condition(z, '<=', invSigma_r + 1)

    blurz = impipe.Function(impipe.Float, "blurz")
    blurz.variableDomain = ([c, x, y, z], [cr, gridrowr, gridcolr, gridintr])
    blurz.definition = impipe.Case(cond, (grid(c, x, y, z-2) + \
                                          grid(c, x, y, z-1) * 4 + \
                                          grid(c, x, y, z  ) * 6 + \
                                          grid(c, x, y, z+1) * 4 + \
                                          grid(c, x, y, z+2)))

    blurx = impipe.Function(impipe.Float, "blurx")
    blurx.variableDomain = ([c, x, y, z], [cr, gridrowr, gridcolr, gridintr])
    blurx.definition = impipe.Case(cond, (blurz(c, x-2, y, z) + \
                                          blurz(c, x-1, y, z) * 4 + \
                                          blurz(c, x  , y, z) * 6 + \
                                          blurz(c, x+1, y, z) * 4 + \
                                          blurz(c, x+2, y, z)))

    blury = impipe.Function(impipe.Float, "blury")
    blury.variableDomain = ([c, x, y, z], [cr, gridrowr, gridcolr, gridintr])
    blury.definition = impipe.Case(cond, (blurx(c, x, y-2, z) + \
                                          blurx(c, x, y-1, z) * 4 + \
                                          blurx(c, x, y  , z) * 6 + \
                                          blurx(c, x, y+1, z) * 4 + \
                                          blurx(c, x, y+2, z)))

    zv = img(x, y) * invSigma_r
    zi = impipe.Cast(impipe.Int, zv)
    zf = zv - zi
    xf = impipe.Cast(impipe.Float, x % sigma_s) / sigma_s
    yf = impipe.Cast(impipe.Float, y % sigma_s) / sigma_s
    xi = x/sigma_s
    yi = y/sigma_s

   
    def lerp(a, b, w):
        return a + w*(b-a)

    xintery0z0 = lerp(blury(c, 2+xi  , 2+yi  , 2+zi  ), \
                      blury(c, 2+xi+1, 2+yi  , 2+zi  ), xf)
    xintery1z0 = lerp(blury(c, 2+xi  , 2+yi+1, 2+zi  ), \
                      blury(c, 2+xi+1, 2+yi+1, 2+zi  ), xf) 
    xinteryinterz0 = lerp(xintery0z0, xintery1z0, yf)

    xintery0z1 = lerp(blury(c, 2+xi  , 2+yi  , 2+zi+1), \
                      blury(c, 2+xi+1, 2+yi  , 2+zi+1), xf)
    xintery1z1 = lerp(blury(c, 2+xi  , 2+yi+1, 2+zi+1), \
                      blury(c, 2+xi+1, 2+yi+1, 2+zi+1), xf)
    xinteryinterz1 = lerp(xintery0z1, xintery1z1, yf)

    xinteryinterzinter = lerp(xinteryinterz0, xinteryinterz1, zf)

    
    interpolated = impipe.Function(impipe.Float, "interpolated")
    interpolated.variableDomain = ([c, x, y], [cr, rowr, colr])
    interpolated.definition = xinteryinterzinter


    filterexpr = impipe.Select(impipe.Condition(interpolated(1, x, y), '>', 0), \
                               interpolated(0, x, y) / interpolated(1, x, y), \
                               img(x, y)) 
    filtered = impipe.Function(impipe.Float, "filtered")
    filtered.variableDomain = ([c, x, y], [cd, rowr, colr])
    filtered.definition = filterexpr

    #####################################################################################
# END
