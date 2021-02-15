# url-shortener
##  Requirements
### Functional requirements
* Given a URL generate a shorter, unique alias for it.
* Redirect users to their original URL when they access the short one.

### Non-Functional Requirements
* Highly avaible system
* Minimum latency

### Other Requirements
* Backend code written in C++ to learn the language
* NoSQL datastore like C* for storage
* Add caching via redis
* Deployed on Docker-compose
* Nginx for load balancing



## API
* Simple API for now:


`createShortURL(string URL)`

`redirectURL(string shortURL)`

## Storage
### Columns
* Hash key
* Long URL

## Infrastructure
* Backend code written in C++ to learn the language
* NoSQL datastore like C* for storage
* Add caching via redis
* Deployed on Docker-compose
* Nginx for load balancing

## Hashing Algo
How can I generate unique keys based on URLs?
### Options
1. UUID -> Base58 encode
    potential implementation: `https://github.com/bitcoin/bitcoin/blob/master/src/base58.cpp`
2. Auto increment DB prim key


