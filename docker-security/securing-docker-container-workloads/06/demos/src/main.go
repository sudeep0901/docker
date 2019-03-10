package main

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"net/http"

    "github.com/gorilla/mux"
)


type Country struct {
	Name  string `json:"name"`
	Capital   string `json:"capital"`
	Continent string `json:"continent"`
}


var database = make(map[string]interface{})


func FindAll() []interface{} {
	items := make([]interface{}, 0, len(database))
	for _, v := range database {
		items = append(items, v)
	}

	return items
}


func FindBy(key string) (interface{}, bool) {
	com, ok := database[key]

	return com, ok
}


func Save(key string, item interface{}) {
	database[key] = item
}


func Remove(key string) {
	delete(database, key)
}


func writeJsonResponse(w http.ResponseWriter, bytes []byte) {
	w.Header().Set("Content-Type", "application/json; charset=UTF-8")
	w.Write(bytes)
}


func SaveCountry(w http.ResponseWriter, r *http.Request) {
	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}

	country := new(Country)
	err = json.Unmarshal(body, country)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}

	Save(country.Name, country)

	w.Header().Set("Location", r.URL.Path+"/"+country.Name)
	w.WriteHeader(http.StatusCreated)
}


func GetCountries(w http.ResponseWriter, _ *http.Request) {
	countries := FindAll()

	bytes, err := json.Marshal(countries)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}

	writeJsonResponse(w, bytes)
}


func GetCountry(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	name := vars["name"]

	country, ok := FindBy(name)
	if !ok {
		http.NotFound(w, r)
		return
	}

	bytes, err := json.Marshal(country)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}

	writeJsonResponse(w, bytes)
}


func UpdateCountry(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	name := vars["name"]

	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}

	country := new(Country)
	err = json.Unmarshal(body, country)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}

	Save(name, country)
}


func DeleteCountry(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	name := vars["name"]

	Remove(name)
	w.WriteHeader(http.StatusNoContent)
}


func main() {
	router := mux.NewRouter().StrictSlash(true)
	sub := router.PathPrefix("/api/v1").Subrouter()
	sub.Methods("POST").Path("/countries").HandlerFunc(SaveCountry)
	sub.Methods("GET").Path("/countries").HandlerFunc(GetCountries)
	sub.Methods("GET").Path("/countries/{name}").HandlerFunc(GetCountry)
	sub.Methods("PUT").Path("/countries/{name}").HandlerFunc(UpdateCountry)
	sub.Methods("DELETE").Path("/countries/{name}").HandlerFunc(DeleteCountry)

	log.Fatal(http.ListenAndServe(":80", router))
}
