import "./App.css";
import Signin from "./components/Signin";
import Register from "./components/Register";
import About from "./components/About";
import Favorite from "./components/Favorite";
import Foster from "./components/Foster";
import Pet from "./components/Pet";
import PetsList from "./components/PetsList";
import Shelters from "./components/Shelters";
import Species from "./components/Species";
import Home from "./components/Home";
import { Routes, Route, Link } from "react-router-dom";
import "bootstrap/dist/css/bootstrap.min.css";
import Nav from "react-bootstrap/Nav";
import Navbar from "react-bootstrap/Navbar";
import NavDropdown from "react-bootstrap/NavDropdown";
import Container from "react-bootstrap/Container";
import Col from "react-bootstrap/Col";
import Row from "react-bootstrap/Row";
import Form from "react-bootstrap/Form";
import Button from "react-bootstrap/Button";
import { useEffect, useState, useCallback } from "react";
import "./App.css";
import PetDataService from "./services/pets";
import MouseParticles from 'react-mouse-particles'
import FavoriteDataService from "./services/favorites"

function App() {
  const [pets, setPets] = useState([]);
  const [user, setUser] = useState(null);
  const [favorites, setFavorites] = useState([]);
  const [doSaveFaves, setDoSaveFaves] = useState(false)
  const [favoritePets, setFavoritePets] = useState([])
  
  const retrieveFavorites = useCallback(() => {
    FavoriteDataService.getAll(user._id)
    .then(response => {
      setFavorites(response.data.favorites);
    })
    .catch(e => {
      console.log(e);
    });
  }, [user]);

  const retrieveFavoritePets = () => {
    PetDataService.getByIdList(favorites)
      .then(response => {
        let sorted = response.data.sort(
          function(a, b) {
            return favorites.indexOf(a._id) - favorites.indexOf(b._id);
          }
        );
        setFavoritePets(
          sorted.map((element) => {
            return ({
              id: element._id,
              name: element.name,
              photo: element.photos[0]
            });
          })
        );
      })
      .catch(e => {
        console.log(e);
      });
  }

  const saveFavorites = useCallback(() => {
    var data = {
      _id: user._id,
      favorites: favorites
    }

    FavoriteDataService.updateFavoritesList(data)
      .catch(e => {
        console.log(e);
      })
  }, [favorites, user])

  useEffect(() => {
    if (user && doSaveFaves) {
      saveFavorites();
      setDoSaveFaves(false);
    }
  }, [user, favorites, saveFavorites, doSaveFaves]);

  useEffect(() => {
    if (user) {
      retrieveFavorites();
    }
  }, [user, retrieveFavorites]);

  useEffect(() => {
    retrieveFavoritePets();
  }, [favorites]);

  const addFavorite = (petId) => {
    setDoSaveFaves(true);
    setFavorites([...favorites, petId])
    console.log(favorites)
  }
  const deleteFavorite = (petId) => {
    setDoSaveFaves(true);
    console.log("delete", favorites)
    setFavorites(favorites.filter(f => f !== petId));
    console.log("delete", favorites)
  }
  const changeOrder = (newFavs) => {
    setDoSaveFaves(true);
    setFavorites(newFavs);
  }



  const retrievePets = useCallback(() => {
    // console.log("fav", favorites)
    PetDataService.getAll()
      .then((response) => {
        setPets(response.data.pets);
      })
      .catch((e) => {
        console.log(e);
      });
  }, [setPets]);

  useEffect(() => {
    retrievePets();
  }, [retrievePets]);

  const onSignout = () => {
      setUser(null)  
    }

  const loadUser = (data) => {
    console.log("data", data)
    setUser({
      _id: data._id,
      name: data.name,
      email: data.email
    })}

  return (
    <div className="App">
      <div>
      <Navbar className="first-line-nav">
        {/* <Container className="container-fluid "> */}
        <Navbar.Brand className="brand" href="/">
          <img
            src="/images/paws-to-hands-logo.png"
            alt="PawsTohands logo"
            className="paws-to-hands-Logo"
          />
          PawsToHands  
        </Navbar.Brand>

  

        {/* <div className="search">
          <Form.Group className="searchbox">
            <Form.Control type="text" placeholder="Search" />
          </Form.Group>
        </div> */}
        <div className="greeting"></div>
        <div className="log-container">
          <Button
            className="register-button"
            style={{ backgroundColor: "#776464"}}
          >
            {!user && <Nav.Link as={Link} to={"/register"}>
              Register
            </Nav.Link>}
            {user && <Nav.Link as={Link} to={"/favorite"}>
              {user.name}
            </Nav.Link>}
          </Button>
          </div>

          <div className="log-container">
          <Button
            className="signin-button"
            style={{ backgroundColor: "#776464" }}
          >
            {!user && <Nav.Link as={Link} to={"/signin"}>
              Sign in
            </Nav.Link>}
            {user && <Nav.Link as={Link} to={"/"} onClick={onSignout}>
              Sign out
            </Nav.Link>}
          </Button>
        </div>
        
     

        <Navbar.Collapse id="responsive-navbar-nav"></Navbar.Collapse>
        {/* </Container> */}
      </Navbar>

      {/* <div className="second-line-nav"> */}
      <Navbar sticky="top" variant="dark" className="sticky second-line-nav">
        <Container className="container-fluid ">
          <Nav.Link as={Link} to={"/"}>
            Home
          </Nav.Link>
          <NavDropdown title="pets" id="nav-dropdown">
            <NavDropdown.Item as={Link} to={"/petslist"}>
              All Pets
            </NavDropdown.Item>
            <NavDropdown.Item as={Link} to={"/species/dog"}>
              <img src="/images/icon-dog.png" className="pets-icon" />
              Dog
            </NavDropdown.Item>
            <NavDropdown.Item as={Link} to={"/species/cat"}>
              <img src="/images/icon-cat.png" className="pets-icon" />
              Cat
            </NavDropdown.Item>
            <NavDropdown.Item as={Link} to={"/species/rabbit"}>
              <img src="/images/icon-rabbit.png" className="pets-icon" />
              Rabbit
            </NavDropdown.Item>
            <NavDropdown.Item as={Link} to={"/species/bird"}>
              <img src="/images/icon-bird.png" className="pets-icon" />
              Bird
            </NavDropdown.Item>
          </NavDropdown>

          <Nav.Link as={Link} to={"/shelters"}>
              Shelters
            </Nav.Link>
          <Nav.Link as={Link} to={"/about"}>
            About
          </Nav.Link>
          <Nav.Link as={Link} to={"/foster"}>
            I am a foster ...
          </Nav.Link>
          <Nav.Link as={Link} to={"/favorite"}>
            Favorite
          </Nav.Link>

          <Navbar.Collapse id="responsive-navbar-nav"></Navbar.Collapse>
        </Container>
      </Navbar>
      {/* </div> */}

      <Routes>
        <Route exact path={"/"} element={<Home pets={pets} />} />
        <Route exact path={"/petslist"} element={<PetsList />} />
        <Route exact path={"/species/:species"} element={<Species />} />
        <Route path={"/signin"} element={<Signin loadUser={loadUser} />} />
        <Route path={"/register"} element={<Register loadUser={loadUser}/>} />
        <Route path={"/favorite"} element={<Favorite
                                              user={user}
                                              favoritePets= { favoritePets }
                                              changeOrder={ changeOrder }
                                            />
                                          } />
        <Route path={"/about"} element={<About />} />
        <Route path={"/foster"} element={<Foster user={user}/>} />
        <Route path={"/pet"} element={<Pet 
                                      user={user}
                                      addFavorite={addFavorite}
                                      deleteFavorite={deleteFavorite}
                                      favorites={favorites}
                                      />} />
        <Route path={"/shelters"} element={<Shelters />} />
        <Route path={"/species"} element={<Home pets={pets} />} />
        <Route path={"/pet/:id/"} element={<Pet 
                                            user={user}
                                            addFavorite={addFavorite}
                                            deleteFavorite={deleteFavorite}
                                            favorites={favorites}/>} />
                                          </Routes>
    </div>
    <div><MouseParticles g={1} num= {4} radius={6} color="random" cull="col,image-wrapper"/></div>
    </div>
  );
}

export default App;
