/*
 * http_answer_code.h
 *
 * Список сообщений http, отправляемых клиенту
 *
 *  Created on: 12.10.2010
 *      Author: knight
 */

#ifndef HTTP_ANSWER_CODE_H_
#define HTTP_ANSWER_CODE_H_

namespace http
{
	/** Запрос клиента обработан успешно, и ответ сервера содержит затребованные данные.  */
	static const char s_200_Ok[] =
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: %d\r\n"
			"Server: web-server\r\n\r\n";

	/** плохой запрос к серверу */
	static const char s_400_Bad_Request[] =
			"HTTP/1.1 400 Bad Request\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 134\r\n"
			"Server: web-server/1.4.26\r\n\r\n"
			"<?xml version=\"1.0\" encoding=\"iso-8859-1\"?><head><title>400 Bad Request</title></head><body><h1>400 Bad Request</h1></body></html>";


	/** Документ по указанному URI не существует. */
	static const char s_404_Not_Found[] =
			"HTTP/1.1 404 Not Found\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 130\r\n"
			"Server: web-server/1.4.26\r\n\r\n"
			"<?xml version=\"1.0\" encoding=\"iso-8859-1\"?><head><title>404 - Not Found</title></head><body><h1>404 - Not Found</h1></body></html>";

	/** Служба временно недоступна */
	static const char s_503_Service_Unavialable[] =
			"HTTP/1.1 503 Service Unavailable\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 146\r\n"
			"Server: web-server/1.4.26\r\n\r\n"
			"<?xml version=\"1.0\" encoding=\"iso-8859-1\"?><head><title>503 Service Unavailable</title></head><body><h1>503 Service Unavailable</h1></body></html>";

	static const char s_ItWorksMsg[] = "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?><head><title>It works!!!</title></head><body><h1>It works!!!</h1></body></html>";


} /* namespace */

#endif /* HTTP_ANSWER_CODE_H_ */
