#include <boost/python.hpp>

BOOST_PYTHON_MODULE(hardware)
{
    using namespace boost::python;
    def("greet", greet);
}
