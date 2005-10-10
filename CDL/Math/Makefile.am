## Source directory

h_sources  = Complex.h FFT.h Math.h Plane.h Primitive.h Random.h Sphere.h Intersection.h Matrix.h Triangle.h Quaternion.h Ray.h Vector.h FixedPoint.h HermiteCurveSegment.h HermiteCurveTangent.h TCBTangent.h CardinalTangent.h CatmullRomTangent.h
cpp_sources = Complex.cpp Math.cpp Plane.cpp Quaternion.cpp Ray.cpp Vector.cpp FFT.cpp Matrix.cpp Triangle.cpp Random.cpp Sphere.cpp FixedPoint.cpp HermiteCurveSegment.cpp HermiteCurveTangent.cpp TCBTangent.cpp CardinalTangent.cpp CatmullRomTangent.cpp

noinst_LTLIBRARIES = libMath.la
libMath_la_SOURCES = $(h_sources) $(cpp_sources)

library_includedir=$(includedir)/CDL/Math
library_include_HEADERS = $(h_sources)

DEFAULT_INCLUDES = -I$(top_srcdir)
.SILENT:
