import axios from "axios";


class FosterDataService{

    submitFosterInfo(data) {
        return axios.put(`${process.env.REACT_APP_API_BASE_URL}/api/v1/pets/foster`, data);
    }
}

export default new FosterDataService()