# pb_sitemap.c

To crawl recursively over https://priceboard.in/sitemap.xml and
    - Find all "www.priceboard.in" and remove "www." from those
    - Find and limit the product names to 255 chararcters 
 
### Run the code
To compile and run the code...
``` sh
    $ gcc pb_sitemap.c -lcurl && ./a.out
```

These directories will be created if they do not exist.
    - priceboard_old  
    - priceboard_old / sitemap
    - priceboard
    - priceboard / sitemap

### Output 
- Existing url contents will be downloaded in the directory "priceboard_old"
- Processed files will be created in the directory "priceboard"
- A file containg only those links which corresponding product names are modified will be stored in "priceboard/Limited_products.txt"
