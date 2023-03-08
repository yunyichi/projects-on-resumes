import axios from "axios";


class ShelterDataService{

    getAll(page = 0) {
        return axios.get(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/shelters`);
    }

    find(query, by="name", page=0) {
        return axios.get(
            `${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/shelters?${by}=${query}&page=${page}`
        );
    } 
    getLocations() {
        return axios.get(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/shelters/locations`);
    }
}

export default new ShelterDataService()