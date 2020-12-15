/*
 * =====================================================================================
 *
 *       Filename:  c_complex.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/11/2020 08:23:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mathieu LEBON (ML), mathieu.lebon@thalesaleniaspace.com
 *   Organization:  Thales Alenia Space
 *
 * =====================================================================================
 */

#ifndef __C_COMPLEX__
#define __C_COMPLEX__

template<typename T>
struct c_complex {

	//bool valid;
	T real;
	T imag;

	c_complex() {
	}

	c_complex(T r, T i) {
		real = r;
		imag = i;
	}

	template<typename T2>
		c_complex(const c_complex<T2> & d) {
			real = d.get_real();
			imag = d.get_imag();
			//valid = d.get_valid();
		}

	c_complex(int d) {
		real = d;
		imag = d;
	}

	T get_real() const {
		return real;
	}

	T get_imag() const {
		return imag;
	}

	//	bool get_valid() const {
	//		return valid;
	//	}

	template<typename T2>
		bool operator==(c_complex<T2> p) {
			return (real == p.real) && (imag == p.imag);
		}

	template<typename T2>
		bool operator!=(const c_complex<T2> p) const {
			return (real != p.real) || (imag != p.imag);
		}

	c_complex<T> operator=(int p) {
		real = imag = p;
		return *this;
	}

	template<typename T2>
		c_complex<T> operator=(const c_complex<T2> p) {
			real = p.get_real();
			imag = p.get_imag();
			//valid = p.get_valid();
			return *this;
		}

	template<int qt>
		c_complex<ap_int<qt+1> > operator+(c_complex<ap_int<qt> > p) {
			c_complex<ap_int<qt+1> > r;
			r.real = real + p.real;
			r.imag = imag + p.imag;
			return r;
		}

	template<typename T2>
		c_complex<T> operator+=(c_complex<T2> p) {
			real += p.real;
			imag += p.imag;
			return *this;
		}

};

#ifndef __SYNTHESIS__
template<typename T2>
inline std::ostream& operator << (std::ostream &os, const c_complex<T2> &x) {
	os << "[" << x.real << ", ";
	os << "" << x.imag << "] ";
	//os << ((x.valid) ? "(vld)" : ""); //.to_string(sc_dt::SC_BIN)
	return os;
}
#endif

#endif

