import React from 'react'
import { Container } from 'react-bootstrap';
import {useState, useEffect} from 'react'
import './Foster.css'

const Foster = ({user}) => {
    const [state, setState] = React.useState({
            species: "",
            age: "",
            breed: "",
            size: "",
            gender: "",
            coatLength: "",
            petName:"",
            location:"",
            email:"",
            phoneNumber:"",
          })
    const [selectedImage, setSelectedImage] = useState(null);

    function handleChange(evt) {
          const value = evt.target.value;
          setState({
            ...state,
            [evt.target.name]: value
          });
        }
    return (
        <div>
        {user ? <Container className='bigContainer'>
        <div className='inputform'>
            <div className='textPromo'>
                <h4>Please fill the following form if you want to look for an adopter.</h4>
            </div>
        <form className='form1'>
            <label>
                Species:
            <input
                name="species"
                type="text"
                value={state.species}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Age:
            <input
                name="age"
                type="text"
                value={state.age}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Breed:
            <input
                name="breed"
                type="text"
                value={state.breed}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Size:
            <input
                name="size"
                type="text"
                value={state.size}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Gender:
            <input
                name="gender"
                type="text"
                value={state.gender}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Coat Length:
            <input
                name="coatLength"
                type="text"
                value={state.coatLegnth}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Pet's Name:
            <input
                name="petName"
                type="text"
                value={state.petName}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Location:
            <input
                name="location"
                type="text"
                value={state.location}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Email:
            <input
                name="email"
                type="email"
                value={state.email}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Phone Number:
            <input
                name="phoneNumber"
                type="text"
                value={state.phoneNumber}
                onChange={handleChange}/>
            </label>
            <br />

            <label>
                Upload Photo:
            <input
                name="uploadPhoto"
                type="file"/>
            </label>
            <br />

            <button type='submit' className='submit_btn' >Submit</button>
        </form>
        </div>
        </Container>
        :
        <div className='f2 center pa6'> You have not signed in, please signin first</div>}
        </div>
    )
}

export default Foster;