/* -*- c++ -*- */

#define EFFECTS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "effects_swig_doc.i"

%{
#include "effects/delay_ff.h"
%}


%include "effects/delay_ff.h"
GR_SWIG_BLOCK_MAGIC2(effects, delay_ff);
