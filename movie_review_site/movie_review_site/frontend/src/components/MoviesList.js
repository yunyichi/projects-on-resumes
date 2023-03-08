import React, {useState, useEffect, useCallback } from 'react'
import MovieDataService from "../services/movies"
import { Link } from "react-router-dom"
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import Card from 'react-bootstrap/Card';
import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';
import Container from 'react-bootstrap/Container';
import {BsStar , BsStarFill} from "react-icons/bs"

import "./MoviesList.css"

const MoviesList = ({user, favorites, addFavorite, deleteFavorite}) => {
  const [movies, setMovies] = useState([])
  const [searchTitle, setSearchTitle] = useState("")
  const [searchRating, setSearchRating] = useState("")
  const [ratings, setRatings] = useState(["All Ratings"])
  const [currentPage, setCurrentPage] = useState(0);
  const [entriesPerPage, setEntriesPerPage] = useState(0)
  const [currentSearchMode, setCurrentSearchMode] = useState("")

  const retrieveRatings = useCallback(() =>{
    MovieDataService.getRatings()
      .then(response =>{
        console.log(response.data)
        setRatings(["All Ratings"].concat(response.data)) 
      })
      .catch( e =>{
        console.log(e)
      });
  }, []);
  
  const retrieveMovies = useCallback(() =>{
    setCurrentSearchMode("");
    MovieDataService.getAll(currentPage)
      .then(response =>{
        setMovies(response.data.movies)
        setCurrentPage(response.data.page)
        setEntriesPerPage(response.data.entries_per_page);
      })
      .catch( e =>{
        console.log(e)
      });
  }, [currentPage]);

  const find = useCallback((query, by) => {
    MovieDataService.find(query, by, currentPage)
    .then(response => {
      setMovies(response.data.movies);
    })
    .catch(e => {
      console.log(e);
    });
  }, [currentPage]);

  const findByTitle = useCallback(() => {
    setCurrentSearchMode("findByTitle")
    find(searchTitle, "title")    
  }, [find, searchTitle]);

  const findByRating = useCallback(() => {
    setCurrentSearchMode("findByRating");
    if(searchRating === "All Ratings"){
      retrieveMovies()
    }
    else{
      find(searchRating, "rated")
    }
  }, [find, searchRating, retrieveMovies]);
  

  const retrieveNextPage = useCallback(() => {
    if(currentSearchMode === "findByTitle") {
      findByTitle();
    } else if (currentSearchMode === "findByRating") {
      findByRating();
    } else {
      retrieveMovies();
    }
  }, [currentSearchMode, findByTitle, findByRating, retrieveMovies]);
  
  useEffect(() => {
    retrieveRatings();
  }, [retrieveRatings])

  useEffect(() => {
    setCurrentPage(0);
  }, [currentSearchMode])

  useEffect(() => {
    retrieveNextPage();
  }, [currentPage, retrieveNextPage]);

  const onChangeSearchTitle = e => {
    const searchTitle = e.target.value
    setSearchTitle(searchTitle);
  }

  const onChangeSearchRating = e => {
    const searchRating = e.target.value
    setSearchRating(searchRating);
  }
  return (
    <div className="App">   
      <Container className='main-container'>
        <Form>        
          <Row>
            <Col>
              <Form.Group className='mb-3'>          
                <Form.Control 
                  type="text" 
                  placeholder="Search by title" 
                  value={searchTitle} 
                  onChange={onChangeSearchTitle} 
                />
              </Form.Group>        
              <Button 
                variant="primary" 
                type="button" 
                onClick={findByTitle}
              > 
                Search         
              </Button>
            </Col>
            <Col>
              <Form.Group className='mb-3'>
                <Form.Control as="select" onChange={onChangeSearchRating} >
                  {ratings.map((rating, i) =>{
                    return(
                      <option value={rating} key={i}>{rating}</option>
                    )
                  })}
                </Form.Control>       
              </Form.Group>    
              <Button 
                  variant="primary" 
                  type="button" 
                  onClick={findByRating}
              > 
                Search         
              </Button>  
            </Col>
          </Row>              
        </Form>  
        
          <Row className='movieRow'>
            {movies.map((movie) =>{
              return(
                <Col key={movie._id}>
                  <Card className='moviesListCard'>
                    { user && (
                      favorites.includes(movie._id) ?
                      <BsStarFill className='start starFill' onClick={() => {
                        deleteFavorite(movie._id);
                      }}/>
                      :
                      <BsStar className='star starEmpty' onClick={() => {
                        addFavorite(movie.id);
                      }}/>
                    )


                    }
                    <Card.Img  className='smallPoster' 
                    src={movie.poster+"/100px180"}
                    onError={(e) => {
                      e.currentTarget.src= '/images/NoPosterAvailable-crop.jpeg';
                    }}
                    />
                    <Card.Body>
                      <Card.Title>{movie.title}</Card.Title>
                      <Card.Text>
                        Rating: {movie.rated}                        
                      </Card.Text>
                      <Card.Text>
                        {movie.plot}                        
                      </Card.Text>                                            
                      <Link to={"/movies/"+movie._id} >View Reviews</Link>
                    </Card.Body>
                  </Card>            
                </Col>                
              )
            })}
          </Row>
          <br />
          Showing page: {currentPage + 1}.
          <Button variant='link' onClick={() => { setCurrentPage(currentPage + 1)}}>
            Get next {entriesPerPage} results            
          </Button>        
      </Container>        
    </div>
  )
}

export default MoviesList;

