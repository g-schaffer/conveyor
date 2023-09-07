
# Configure Arduino IDE
```
https://blog.flozz.fr/2019/06/16/decouverte-du-m5stack-un-bon-kit-de-developpement-pour-lesp32
```

# Prerequist
- Install Docker
- Install Docker-compose

# Server address change
	- If the server address change you need change the address in :
		- ./esApp/src/main.cpp
		- ./.env
        
### WARNING for ESP32
// ============================= WARNING ===============================
// You need : 
// 1- On WifiUtils.h change the WIFI_SSID and WIFI_PASSWORD in define
// 2- Connect your desktop to this Acces-Point
// 3- Run the api
// 4- Change the SERVER_ADDRESS in define on 
// =====================================================================

# Commands

## Run the project
    - docker-compose up --build
    - Create super user :
        - docker exec -it convoyor_api python manage.py createsuperuser

    - Configure your desktop for build ESP
        - https://blog.flozz.fr/2019/06/16/decouverte-du-m5stack-un-bon-kit-de-developpement-pour-lesp32/  

## Run migration
    - Run the container
    - docker exec -it convoyor_api /bin/bash -c "python manage.py makemigrations && python manage.py migrate --traceback"

## Dump fixture
    - Run the container
    - docker exec -it convoyor_api /bin/bash -c "python manage.py dumpdata > db_dumped.json"

## Load fixture
    - Run the container
    - docker exec -it convoyor_api /bin/bash -c "python manage.py loaddata db.json"
    
## Build documentation

Install doxygen :  
    - apt-get install doxygen

Run doxygen : 
    - doxygen Doxyfile

To access documentation go to ./html/index.html

## Run test in terminal

Install platformio :
    - apt-get install platformio
Export path :
    - export PATH=$PATH:/home/$USER/.platformio/penv/bin/
Load testing fixture: 
    - docker exec -it convoyor_api /bin/bash -c "python manage.py loaddata ./convoyeur/fixture_test.json"
Run test :
    - pio test -v


Running test is also available in vscode, check doc of platformio
 
## Video
https://youtube.com/shorts/YNBH0iPfFyU?feature=share

## Resolve errors
Error 1 :  A fatal error occurred: Could not open /dev/ttyUSB0, the port doesn't exist
	Solution : https://docs.platformio.org/en/latest/core/installation/udev-rules.html
