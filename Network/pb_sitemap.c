/* crawl recursively https://priceboard.in/sitemap.xml 
 * to replace all "www.priceboard.in" by "priceboard.in".
 * Also limit the product names to maximum of 255 characters.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <curl/curl.h>

int grep_url(char *);
int url2file(char *, char *);
int f_replace_str(char *, char *, const char *, const char *);
int limit_product_name(char *, int);

char url[256][2083];

int main()
{
	char fname[100], foutname[100]; 
	FILE *fp, *fp_out;

	struct stat st = {0};
	if (stat("priceboard_old", &st) == -1) {
    	mkdir("priceboard_old", 0777);
	}
	if (stat("priceboard", &st) == -1) {
    	mkdir("priceboard", 0777);
	}
	if (stat("priceboard_old/sitemap", &st) == -1) {
    	mkdir("priceboard_old/sitemap", 0777);
	}
	if (stat("priceboard/sitemap", &st) == -1) {
    	mkdir("priceboard/sitemap", 0777);
	}

     	sprintf(fname, "priceboard_old/sitemap.xml");
     	sprintf(foutname, "priceboard/sitemap.xml");

	char url1[] = "https://priceboard.in/sitemap.xml";

	if (url2file(url1, fname) != 0) {
		printf("Unable to download %s\n", url1);
		exit(1);
	}
	f_replace_str(fname, foutname,
			"https://www.priceboard.in",
			"https://priceboard.in");

	int nlink;
	nlink = grep_url(foutname);

	FILE *flimit;	
	flimit = fopen("priceboard/Limited_products.txt", "w");
	fclose(flimit);

	for (int i = 0; i < nlink; ++i) {
	       	sprintf(fname,
			"priceboard_old/sitemap/products_%d.xml", i);
	       	sprintf(foutname,
			"priceboard/sitemap/products_%d.xml", i);

		if (url2file(url[i], fname) != 0)
			exit(1);

		f_replace_str(fname, foutname,
			"https://www.priceboard.in",
		       	"https://priceboard.in");

		limit_product_name(foutname, 200);
	}
	return 0;
}

static size_t write_data(void *ptr, size_t size, size_t nmemb,
					 	void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

int url2file(char *url, char *fname)
{
	printf("\nDownloading %s\n", url);

	CURL *curl;

	FILE *fp;
	fp = fopen(fname, "w");

	// initialize curl season
	curl = curl_easy_init();

	// set URL
	curl_easy_setopt(curl, CURLOPT_URL, url);

	// if the site is set to redirect to other locations
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	// assign function for data write operation
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

	if (fp) {
		// write the page body to this file
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		// perform curl operations
		curl_easy_perform(curl);
	}
	fclose(fp);

	printf("Downloaded file..\n");
	return 0;
}

int f_replace_str(char *fname, char *foutname,
		const char *in_str, const char *out_str)
{
	char ch;
	int i = 0;
	int count = 0;

	FILE *fp, *fp_out;
	fp = fopen(fname, "r");
	fp_out = fopen(foutname, "w+");

	if (fp == NULL) {
		printf("Can not read %s\n", fname);
		exit(1);
	}
	if (fp_out == NULL) {
		printf("Can not write %s\n", foutname);
		exit(1);
	}

	int str_len;	
        str_len = strlen(in_str);

	while ((ch = fgetc(fp)) != EOF) {
		if (ch == in_str[i] && i < str_len) {
			++i;

			// if all charactrs of in_str match
			if (i == str_len) {
				fputs(out_str, fp_out);
				i = 0;
				++count;
			}
		} else if (i > 0) {
			for (int n = 0; n < i; ++n)
				fputc(in_str[n], fp_out);
			fputc(ch, fp_out);
			i = 0;
		} else {
			fputc(ch, fp_out);
		}
	}

	fclose(fp_out);
	fclose(fp);

	printf("%d strings matched and replaced\n", count);
	return 0;
}

int grep_url(char *fname) 
{
	/* Search all urls in file pointed 'fname'
	 * and store in external veriable url[][]
	 * return no of url found
	 */
	
	char ch, temp[6]; 
	int i, m, n, flag;
	i = m = n = flag = 0;

	char s1[5] = "<loc>";
	char  s2[6] = "</loc>";

	FILE *fp;
	fp = fopen(fname, "r");

	while ((ch = fgetc(fp)) != EOF) {
		if (flag == 0){ // not url, outside <loc> </loc>
		      	if (ch == s1[i] && i == 4) {
				flag = 1, i = 0;
			} else if (ch == s1[i]) {
				++i;
				continue;
			} else if (i != 0) {
				i =0;
			}
		} else if (flag == 1) { // url, between <loc> </loc>
			if (ch == s2[i] && i < 5) {
				temp[i] = ch;
				++i;
				continue;
			} else if (ch == s2[i] && i == 5) {
				flag = 0, i = 0;
				url[n][m] = '\0';
				m = 0;
				++n;
				continue;
			} else if (ch != s2[i] && i == 0) {
				url[n][m] = ch;
				++m;
			} else if (ch != s2[i] && i > 0) {
				for (int j = 0; j < i; ++j) {
					url[n][m] = temp[j];
					++m;
					i=0;
				}
			}
		}
	}

	fclose(fp);

	printf("%d url obtained\n", n);
	return n;
}

int limit_product_name(char *foutname, int max_size) {
	int urlflag = 0;
	char ch, buffer[2048]; 
	char s1[] = "<loc>https://priceboard.in/"; 

	FILE *ftemp, *fp, *flimit;
	flimit = fopen("priceboard/Limited_products.txt", "a");
	fp = fopen(foutname, "r");
	ftemp = fopen("temp.xml", "w+");

	if (fp == NULL || ftemp == NULL || flimit == NULL)
		exit(2);

	int i = 0, len;
	len = strlen(s1);

	fputs(foutname, flimit);
	fputc('\n', flimit);

	while ((ch = fgetc(fp)) != EOF) {
		fputc(ch, ftemp);

		if (ch == s1[i] && i < len-1) {
			++i;
			continue;
		} else if (ch == s1[i] && i == len-1) {
			i = 0;

			int n = 0;
			while ((ch = fgetc(fp)) != '/') {
				buffer[n] = ch;
				++n;
			}

			if (n > max_size) {
				buffer[max_size] = '\0';
			
				fputs(s1, flimit);
				fputs(buffer, flimit);
				fputc(ch, flimit);
			
				fputs(buffer, ftemp);
				fputc(ch, ftemp);
				
				while ((ch = fgetc(fp)) != '<') {
					fputc(ch, ftemp);
					fputc(ch, flimit);
				}
				fputc(ch, ftemp);
				fputc('\n', flimit);
			} else { 
				(buffer[n] = '\0');
				fputs(buffer, ftemp);
				fputc(ch, ftemp);
			}
			continue;
		} else if (ch != s1[i] && i > 0) {
			i = 0;
			continue;
		}
	}
	fclose(flimit);
	fclose(fp);

	// copy content of temp file to the original file
	fp = fopen(foutname, "w");
	if (fp == NULL)
		exit(3);
	
	fseek(ftemp, 0, SEEK_SET);
	
	while ((ch = fgetc(ftemp)) != EOF)
		fputc(ch, fp);

	fclose(ftemp);
	fclose(fp);

	printf("Product name limitd to %d characters\n", max_size);
	return 0;
}
