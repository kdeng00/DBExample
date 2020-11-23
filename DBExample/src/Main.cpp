#include <iostream>
#include <string>
#include <exception>


#include <soci/soci.h>
#include <soci/soci-backend.h>
#include <soci/odbc/soci-odbc.h>

#pragma comment(lib, "soci_core_4_0.lib")
#pragma comment(lib, "soci_odbc_4_0.lib")


template<typename Val, typename Str>
class JobMessageQueue
{
public:
	JobMessageQueue() = default;
	JobMessageQueue(Val id) : rec_id(id)
	{
	}


	Val rec_id;
	Str user_id;
	Str message;
	Str occurred;
};


template<typename Message>
void print_message(const Message &message)
{
	std::cout << "Rec_id: " << message.rec_id << "\n";
	std::cout << "UserID: " << message.user_id << "\n";
	std::cout << "Occurred: " << message.occurred << "\n";
	std::cout << "Message: " << message.message << "\n";
}


int main()
{
	std::cout << "Starting DBExample\n";


	try
	{
		const std::string dsn_path("filedsn=C:\\ViperSQL.dsn");

		// soci::backend_factory const &back_end = *soci::factory_odbc();
		const auto &back_end = *soci::factory_odbc();
		soci::session sql(back_end, dsn_path);

		constexpr auto record_id = 1172163;

		auto message = JobMessageQueue<int, std::string>(record_id);

		sql << "SELECT Rec_id, UserID, Message, Occurred FROM [JobMessageQueue] "
			<< "WHERE Rec_id = :Rec_id",
			soci::into(message.rec_id), soci::into(message.user_id),
			soci::into(message.message), soci::into(message.occurred),
			soci::use(record_id, "Rec_id");

		print_message <JobMessageQueue<int,std::string>>(message);
	}
	catch (std::exception &ex)
	{
		std::cout << "An error occurred\n";
		std::cout << ex.what() << "\n";
	}


	return 0;
}