import React, {useState, useEffect, useCallback } from 'react'
import PetDataService from "../services/pets"
import { Link } from "react-router-dom"
import Card from 'react-bootstrap/Card';
import Row from 'react-bootstrap/Row';
import Container from 'react-bootstrap/Container';
import "./PetsList.css"


const PetsList = () => {
    const [pets, setPets] = useState([]);
    const [page, setPage] = useState(1);
    const [totalPage, setTotalPage] = useState([]);

    const setCurrentPage = value => {
      setPage(value)
      console.log(page)
    }

    const updatePage = () => {
      setPage(page+1)
      console.log(page)
    }

    const backPage = () => {
      setPage(page-1)
      console.log(page)
    }


    const retrievePets = useCallback(() =>{
        PetDataService.getAll(page-1)
          .then(response =>{
            setPets(response.data.pets)
            let numbers = []
            for (let i = 1; i <= Math.ceil(response.data.total_results/12); i++) {
              numbers.push(i)
            }
            setTotalPage(numbers)
            // console.log(totalPage)
          })
          .catch( e =>{
            console.log(e)
          });
      }, [setPets, page]);
    
      useEffect(() => {
        retrievePets();
      }, [retrievePets, page])

      // const getPageContent = totalPage => {
      //   let content = [];
      //   numbers = []
      //   for (let i = 1; i <= totalPage; i++) {
      //     numbers.push(i)
      //   }
      //   numbers.map(n => (

      //   ))
      //   content.push(<li class="page-item"><a key={i} href="#" className="page-link" onClick={setCurrentPage(i)}>{i}</a></li>);
      //   return content;
      // };
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
        <nav aria-label="Page navigation" className='pa5'>
          <ul class="pagination justify-content-center">
            <li class={`page-item ${page == 1 ? 'disabled' :''}`}>
              <a class="page-link f3 navy" href="#" onClick={() => backPage()}>Previous</a>
            </li>
            {totalPage.map(num => (
              <li key={num} class={`page-item ${page == num ? 'disabled' :''}`}>
                <a href="#" className="page-link f3 navy" onClick={() => setCurrentPage(num)}>{num}</a></li>
            ))}
            <li class={`page-item ${page == totalPage.slice(-1) ? 'disabled' :''}`}>
              <a class="page-link f3 navy" onClick={() => updatePage()} href="#">Next</a>
            </li>
          </ul>
        </nav>        
      </div>
    )
  }
  
  export default PetsList;