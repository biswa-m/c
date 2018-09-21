//Read url and display it

#include <stdio.h>
#include <curl/curl.h>

int main()
{
	CURL* curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "curl initialization failure");
		return 128;
	}
	CURLcode res = CURLE_OK;

	if ((res = curl_easy_setopt(curl, CURLOPT_URL,
			"https://priceboard.in/sitemap.xml")) 
			!= CURLE_OK) {
	 	fprintf(stderr, "%s", curl_easy_strerror(res));
	 	return 1;
	}
	if ((res = curl_easy_perform(curl)) != CURLE_OK ) {
		fprintf(stderr, "%s", curl_easy_strerror(res));
		return 1;
	}
	curl_easy_cleanup(curl);
	return 0;
}
