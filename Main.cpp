#include <iostream>
#include <thread>
#include <string>
#include <mutex>
class Loger {
public:
	void log(const std::string& msg) {
		std::lock_guard<std::mutex> lock(_mutex);
		std::cout << "[" << _messageCounter << "]" << msg << '\n';
		_messageCounter++;
	}
private:
	std::mutex _mutex;
	int _messageCounter = 0;
};
int main(){
	setlocale(LC_ALL, "Russian");
	Loger logger;
	logger.log("Hello");
	logger.log("info msg");
	std::thread t1 = std::thread([&logger]() {//имя дается чтобы закрыть поток|: t1.join()
		std::string	threadName = "t1";
		for (size_t i = 0; i < 100; i++)		{
			logger.log(threadName + " doing " + std::to_string(i) + " iteration of work\n");
		}
		});
	std::thread t2 = std::thread([&logger]() {//имя дается чтобы закрыть поток|: t2.join()
		std::string	threadName = "t2";
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + " doing " + std::to_string(i) + " iteration of work\n");
		}
		});
	//race-condition - состояние гонки
	t1.join();
	t2.join();
	return 0;
}