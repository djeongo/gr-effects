/* -*- c++ -*- */
/* 
 * Copyright 2017 Jeong-O Jeong.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <volk/volk.h>
#include <fftw3.h>
#include "pitch_detector_ff_impl.h"

namespace gr {
  namespace effects {

    pitch_detector_ff::sptr
    pitch_detector_ff::make(int n_fft_)
    {
      return gnuradio::get_initial_sptr
        (new pitch_detector_ff_impl(n_fft_));
    }

    /*
     * The private constructor
     */
    pitch_detector_ff_impl::pitch_detector_ff_impl(int n_fft)
      : gr::block("pitch_detector_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      n_fft_ = n_fft;
      std::cout << "FFT size in samples : " << n_fft_ << std::endl;
      input_buffer_ = (float *)calloc(n_fft_, sizeof(float));
      output_buffer_ = (float *)calloc(n_fft_, sizeof(float));

      d_inbuf_ = (float *) volk_malloc (sizeof (float) * inbuf_length (), volk_get_alignment ());
      if (d_inbuf_ == 0) {
        throw std::runtime_error ("volk_malloc");
      }
      d_outbuf_ = (gr_complex *) volk_malloc (sizeof (gr_complex) * outbuf_length (), volk_get_alignment ());
      if (d_outbuf_ == 0) {
        volk_free (d_inbuf_);
        throw std::runtime_error ("volk_malloc");
      }
      /*
       * The first argument, n, is the size of the transform you are trying to compute.
       * The size n can be any positive integer, but sizes that are products of small
       * factors are transformed most efficiently (although prime sizes still
       * use an O(n log n) algorithm).
       *
       * The next two arguments are pointers to the input and output arrays of the transform.
       * These pointers can be equal, indicating an in-place transform.
       *
       * The fourth argument, sign, can be either FFTW_FORWARD (-1) or
       * FFTW_BACKWARD (+1), and indicates the direction of the transform
       * you are interested in; technically, it is the sign of the exponent in the transform.
       *
       * The flags argument is usually either FFTW_MEASURE or FFTW_ESTIMATE.
       * FFTW_MEASURE instructs FFTW to run and measure the execution time of
       * several FFTs in order to find the best way to compute the transform of size n.
       * This process takes some time (usually a few seconds), depending on
       * your machine and on the size of the transform.
       * FFTW_ESTIMATE, on the contrary, does not run any computation
       * and just builds a reasonable plan that is probably sub-optimal.
       * In short, if your program performs many transforms of the same size
       * and initialization time is not important, use FFTW_MEASURE; otherwise use the estimate.
       */
      d_plan_ = fftwf_plan_dft_1d (n_fft_,
                        reinterpret_cast<fftwf_complex *>(d_inbuf_),
                        reinterpret_cast<fftwf_complex *>(d_outbuf_),
                        FFTW_FORWARD,
                        FFTW_MEASURE);
      if (d_plan_ == NULL) {
        fprintf(stderr, "gr::fft: error creating plan\n");
        throw std::runtime_error ("fftwf_plan_dft_1d failed");
      }
    }

    /*
     * Our virtual destructor.
     */
    pitch_detector_ff_impl::~pitch_detector_ff_impl()
    {
      free(input_buffer_);
      free(output_buffer_);
    }

    void
    pitch_detector_ff_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    /*
     * Left shift input buffer
     */
    void pitch_detector_ff_impl::shift_left()
    {
      memmove((void *)input_buffer_, (void *)&input_buffer_[1], sizeof(float)*(n_fft_-1));
//      memmove((void *)output_buffer_, (void *)&output_buffer_[1], sizeof(float)*(n_fft-1));
    }

    int
    pitch_detector_ff_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];


      std::cout << "noutput_items " << noutput_items <<std::endl;
      for(int i=0; i<noutput_items; i++){
        shift_left();
        // push into buffer
        input_buffer_[n_fft_-1] = in[i];
        // take FFT of the window

//        fftwf_execute((fftwf_plan) d_plan_);
        // copy result to output stream
        //memcpy(out, d_fft->get_outbuf(), output_data_size);

        // generate new output sample
        out[i] = in[i];
      }
      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace effects */
} /* namespace gr */


