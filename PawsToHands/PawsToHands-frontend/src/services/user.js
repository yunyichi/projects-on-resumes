import axios from "axios";


class UserDataService{

    register(data){
        // data = JSON.stringify(data);
        // console.log(data)
        return axios.post(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/register`, data)
    }
    login(data){
        // data = JSON.stringify(data);
        return axios.post(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/login`, data)
    }
}

export default new UserDataService()