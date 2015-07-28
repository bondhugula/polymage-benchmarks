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
