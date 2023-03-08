import React, {useState, useEffect, useCallback } from 'react'
import {Link, useParams, useLocation} from 'react-router-dom'
import PetDataService from "../services/pets"
import Card from 'react-bootstrap/Card';
import Row from 'react-bootstrap/Row';
import Container from 'react-bootstrap/Container';
import "./Species.css"




const Species = props => {
    let params = useParams();
    const [pets, setPets] = useState([]);

    const retrievePets = useCallback(() =>{
        //console.log("good")
        PetDataService.getBySpecies(params.species)
          .then(response =>{
            //console.log("response data", response)
            setPets(response.data)
            console.log("current", pets)
          })
          .catch( e =>{
            console.log(e)
          });
      }, [setPets, params.species]);
    
      useEffect(() => {
        retrievePets();
      }, [retrievePets, params.species])

    return (
      <div className="App">
        <Container className='main-container'>
        <Row className='petsRow flex-wrap'>
              {pets.map((pet) =>{
                return(
                    <Card className='petsListCard w-33 code'>
                      <Card.Img  className='smallPoster tc grow br3 pa3 ma2 dib bw2 shadow-5 br-100 dib ba b--black-05 pa2'
                      src={pet.photos[0]}
                      />
                      <Card.Body className='center'>
                        <Card.Text className='tc f3 mb2 black'>{pet.name}</Card.Text>                                            
                        <Link className='f5 fw4 gray mt0 center' to={"/pet/"+pet._id} >View Details</Link>
                      </Card.Body>
                    </Card>               
                )
              })}
            </Row>      
        </Container>        
      </div>
    )
  }
  
  export default Species ;