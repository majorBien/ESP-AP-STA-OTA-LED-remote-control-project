idf_component_register(SRCS  "main.c" "http_server.c" "wifi_app.c" "io.c" "nvs_utils.c" "wifi_sta.c"
                       INCLUDE_DIRS "."
                        EMBED_FILES "webpage/favicon.ico" 
                        "webpage/index.html" 
                        "webpage/app.js" 
                        "webpage/app.css"  
                        "webpage/jquery-3.3.1.min.js"
                       )
                       
                       
