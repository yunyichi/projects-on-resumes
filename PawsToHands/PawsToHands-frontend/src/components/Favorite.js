import Container from 'react-bootstrap/esm/Container';
import "./Favorites.css"
import Row from "react-bootstrap/Row";
import { Link } from "react-router-dom"
import 'react-slideshow-image/dist/styles.css'
import { Zoom } from 'react-slideshow-image';
import 'react-slideshow-image/dist/styles.css'

const style = {
  width: 400
}

const Favorite = ({
    user,
    favoritePets }) => {
    return (
      <div>
          {user ? <div>
         <Container>
             <Row>
          <div className="f2 center favorite-title">
                My Favorites
          </div>
          </Row>

        <div className="slide-container">
            <Zoom scale={0.4} indicators={true}>
            {
                favoritePets.map((each, index) => <div className='center each-slide-effect'>
                                                    <Link to={"/pet/"+each.id}><img className='center' key={index} style={{width: "457px", height: "457px"}} src={each.photo} /></Link>
                                                  </div>)
            }
            </Zoom>
            <div className='center code f3'>Your pets are waiting here! Choose one to take home</div>
        </div>
          {/* <Row>
          <div className='flex flex-wrap w-100' >
          {favoritePets.map((pet) =>{
                return(
                    <Card className='petsListCard w-33 code'>
                      <Card.Img  className='smallPoster tc grow br3 pa3 ma2 dib bw2 shadow-5 br-100 dib ba b--black-05 pa2'
                      src={pet.photo}
                      />
                      <Card.Body className='center'>
                        <Card.Text className='tc f3 mb2 black'>{pet.name}</Card.Text>                                            
                        <Link className='f5 fw4 gray mt0 center' to={"/pet/"+pet.id} >View Details</Link>
                      </Card.Body>
                    </Card>               
                )
              })}
          </div>
          </Row> */}

         </Container>
        </div>
        :
        <div className='f2 center pa6'> You have not signed in, please signin first</div>}
        </div>
    )
  }
  
  export default Favorite;
