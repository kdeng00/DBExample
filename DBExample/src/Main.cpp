#include <iostream>
#include <string>
#include <exception>


#include <soci/soci.h>
#include <soci/soci-backend.h>
#include <soci/odbc/soci-odbc.h>

#pragma comment(lib, "soci_core_4_0.lib")
#pragma comment(lib, "soci_odbc_4_0.lib")


int main()
{
	std::cout << "Hello\n";


	try
	{
		const std::string dsn_path("filedsn=C:\\ViperSQL.dsn");

		soci::backend_factory const &back_end = *soci::factory_odbc();
		soci::session sql(back_end, dsn_path);
	}
	catch (std::exception &ex)
	{
		std::cout << "An error occurred\n";
		std::cout << ex.what() << "\n";
	}


	return 0;
}