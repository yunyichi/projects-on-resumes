import axios from "axios";


class PetDataService{

    // getAll(page = 0){
    //     return axios.get(`${process.env.REACT_APP_API_BASE_URL}/api/v1/movies?page=${page}`)
    // }
    getAll(page = 0){
        return axios.get(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets?page=${page}`)
    }

    getSpecies(){
        return axios.get(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/species`);
    }
    get(id){         
        return axios.get(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/id/${id}`)
    }
    getBySpecies(species){
        console.log("start search species")
        return axios.get(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/species/${species}`)
    }

    getByIdList(idList) {
        let listString = JSON.stringify(idList);
        return axios.get(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/idList/${listString}`);
      }
}

export default new PetDataService()