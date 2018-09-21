// write url contents to file

#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, 
		void *stream) {
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

int main() 
{
	CURL *curl;
	static const char *pagefilename = "page.out";
	FILE *f_page;

	// initialize curl season
	curl = curl_easy_init();

	// set URL
	curl_easy_setopt(curl, CURLOPT_URL, "google.com");

	// if the site is set to redirect to other locations
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	// assign function for data write operation
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

	// open the file
	f_page = fopen(pagefilename, "wb"); 
	if (f_page) {
		
		// write the page body to this file	
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, f_page);

		// perform curl operations
		curl_easy_perform(curl);

		fclose(f_page);
	}

	return 0;
}
