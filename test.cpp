#include <iostream>	//cout
#include <memory>
#include <sstream> 
#include "TCPClient.h"
#include "TCPSSLClient.h"

#define PRINT_LOG [](const std::string& strLogMsg) { std::cout << strLogMsg << std::endl;  }

using namespace std;

int main(){

	
	unique_ptr<CTCPSSLClient> m_pSSLTCPClient;

	m_pSSLTCPClient.reset(new CTCPSSLClient(PRINT_LOG));
	//m_pSSLTCPClient->SetSSLKeyFile(SSL_KEY_FILE); // not mandatory
        m_pSSLTCPClient->SetSSLCerthAuth("/home/pi/ca_cert.pem");///ca_cert.pem"); // not mandatory

	bool bRet = m_pSSLTCPClient->Connect("192.168.10.90", "8000");
	stringstream ss;
	ss << "GET /rest/throttling HTTP/1.1 \r\n\r\n";
	bRet = m_pSSLTCPClient->Send(ss.str());
	cout << "Sent message( " << bRet <<" ): " << ss.str() << endl;

	char buffer[15];
	cout << "starting read"<< endl;
	int res_size =  m_pSSLTCPClient->Receive(buffer, 9);

	cout << buffer  << endl;
}
