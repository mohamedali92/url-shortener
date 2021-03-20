# url-shortener
##  Requirements
### Functional requirements
* Given a URL generate a shorter, unique alias for it.
* Redirect users to their original URL when they access the short one.x


### Other Requirements
* Backend code written in C++ to learn the language
* Backed by PostgresSQL DB
* Add caching via redis
* Deployed on Docker-compose
* Deployed to Heruko PAAS

### Setup instructions

- Build `cppbox` docker container:

```cd infra/cppbox/```
  
```docker build -t cppbox . ```

- Build `url` container, while in the root dir

```docker build -t url . ```

- Setup project using docker-compose

```docker-compose up ```


### Usage instructions
- Once the container is up you can get a shortened url as follows:


```
curl -X GET http://localhost:8080/create_new_url \
  -H 'Content-Type: application/json' \
  -H 'Postman-Token: f6976969-713c-4a48-9042-09e4bea2c89d' \
  -H 'cache-control: no-cache' \
  -d '{"url": "https://apple.com"}'
  ```

- Then you can open a webbrowser and navigate to and you should be redirected to the original url

```localhost:8080/<short code from previous step>```