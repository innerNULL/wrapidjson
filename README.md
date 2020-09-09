# wrapidjson
The name comes from "WRApped raPIDJSON, wrapidjson".  
  
The original intention of this project is, using some simple but convinent wrappers improve the development efficiency for the projects based on rapidjson(https://github.com/Tencent/rapidjson) project.
  
The processing json should be easy, there are just a few limited case for most user to handling json:  
* create a json object.
* insert/update a new key-value pair into an existing json object.
* remove an existing key-value pair from a json object.
* query certain type data from json object to a c++ data struct.
* convert a json object to string.

The purpose of this project is, for basical json using case, decrease the developing code lines comparing with using the original rapidjson lib.

