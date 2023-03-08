import React from 'react'
import { useEffect, useState, useCallback} from 'react';
import Button from 'react-bootstrap/Button';
import Card from 'react-bootstrap/Card';
import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';import PetDataService from "../services/pets"
import Container from 'react-bootstrap/Container';
import "./Species.css"
import { Link } from "react-router-dom"
import "./Home.css"

const Home = props => {
    const [species, setSpecies] = useState([]);
    const retrieveSpecies = useCallback(() =>{
        PetDataService.getSpecies()
          .then(response =>{
            //   console.log(response)
            setSpecies(response.data)
          })
          .catch( e =>{
            console.log(e)
          });
      }, [setSpecies]);
    
      useEffect(() => {
        retrieveSpecies();
        console.log("species", species)
      }, [retrieveSpecies])

    return (
        <div>
          <div className='background' > 
          <img class="homepage-image" src="images/homepage-background.png" alt="iphone-mockup"/>
            <h1>
            We are waiting for you...
            </h1>
              
          </div>
         


            <Container className="species-container"> 
              
            <Row className='mw9 flex justify-between center ph3-ns spcies-row'>
              {species.map((s) =>{
                  if (s === 'dog') {
                    return(
                        <a href="/species/dog" className='w-20'>
                        <div className='tc  grow br3 pa3 ma2 dib bw2 shadow-5 species-box'>
                            <img className='spcies-image' alt='species' src="/images/dog.png"
                         />
                            <div>
                                <h2>{s}</h2>
                            </div>
                        </div>
                        </a>
                                     
                    )
                  } else if (s === 'cat') {
                    return(
                      <a href="/species/cat" className='w-20'>
                        <div className='tc grow br3 pa3 ma2 dib bw2 shadow-5 species-box'>
                            <img className='spcies-image' alt='species' src="/images/cat.png"
                           />
                            <div>
                                <h2>{s}</h2>
                            </div>
                        </div>
                      </a>
                                     
                    )
                  } else if (s === 'bird') {
                    return(
                      <a href="/species/bird" className='w-20'>
                        <div className='tc grow br3 pa3 ma2 dib bw2 shadow-5 species-box'>
                            <img className='spcies-image' alt='species' src="/images/bird.png"
                            />
                            <div>
                                <h2>{s}</h2>
                            </div>
                        </div>
                        </a>             
                    )                  
                } else if (s === 'rabbit') {
                    return(
                      <a href="/species/rabbit" className='w-20'>
                        <div className='tc grow br3 pa3 ma2 dib bw2 shadow-5 species-box'>
                            <img className='spcies-image' alt='species' src="/images/rabbit.png"
         />
                            <div>
                                <h2>{s}</h2>
                            </div>
                        </div>
                        </a>               
                    )
                }
                
              })}
            </Row>      
        </Container>
        <hr/>
        <h1 className='tc'>Find pets for you ...</h1>
        <div className='mw10 center ph1-ns'>
        <Container className='main-container'>
        <Row className='flex justify-between'>
        {props.pets.slice(0,3).map((pet) =>{
                return(
                  <Col className='w-25'>
                    <Card className='bg-light-gray br3 pa3 ma2 dib bw2 shadow-5 code'>
                      <Card.Img  className='smallPoster grow br-100 dib ba b--black-05 pa2'
                      src={pet.photos[0]}
                      width='312px' height='357px'
                      />
                      <Card.Body className='center'>
                        <Card.Text className='tc f3 mb2 black'>{pet.name}</Card.Text>
                        <Link className='f5 fw4 gray mt0 center' to={"/pet/"+pet._id} >View Details</Link>
                      </Card.Body>
                    </Card>
                    </Col>               
                )
              })}
        <Col className='w-25 '>
        <Card className=' bg-light-gray br3 pa3 ma2 dib bw2 shadow-5 code'>
                      <Card.Img  className='smallPoster br-100 dib ba b--black-05 pa2' 
                      src="/images/more.png" alt="PawsTohands logo"
                      width='312px' heigh='357px'
                      />
                      <Card.Body className='center'>
                        <Card.Text className='tc f3 mb2 black'>Meet more ...</Card.Text>                                             
                        <Link className='f5 fw4 gray mt0' to={"/petslist"} >Click here for more...</Link>
                      </Card.Body>
                    </Card>
                    </Col>
          </Row> 
          </Container> 
        </div>
        </div>
    )
}

export default Home;