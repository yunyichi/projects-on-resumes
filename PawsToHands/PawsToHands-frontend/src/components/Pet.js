import React from "react";
import { Link, useParams, useLocation } from "react-router-dom";
import { useState, useEffect } from "react";
import PetDataService from "../services/pets";
import Card from "react-bootstrap/Card";
import Col from "react-bootstrap/Col";
import Row from "react-bootstrap/Row";
import Container from "react-bootstrap/Container";
// import { BsStar, BsStarFill} from"react-icons/bs";
import { FcLikePlaceholder, FcLike} from "react-icons/fc";

const Pet = ({user, addFavorite, deleteFavorite, favorites}) => {
  let params = useParams();
  const [pet, setPet] = useState({
    _id: "",
    name: "",
    species: "",
    breed: [],
    age: "",
    gender: "",
    color: "",
    spayed_or_neutered: true,
    vaccinations_up_to_date: true,
    photos: [],
    location: "",
  });

  useEffect(() => {
    const getPet = (id) => {
      console.log("user",user, addFavorite, deleteFavorite, favorites)
      PetDataService.get(id)
        .then((response) => {
          setPet(response.data);
          console.log(response.data);
          console.log("fav", favorites)
        })
        .catch((e) => {
          console.log(e);
        });
    };
    getPet(params.id);
  }, [params.id]);
  console.log(pet);
  return (
    <div>
      <Container className="main-container">
        <Row className="petRow  flex justify-center">
          <h1>Images</h1>
          {pet.photos.map((p) => {
            return (
              <Card className="petsListCard tc w-25">
                <Card.Img
                  className="smallPoster grow bg-light-gray br3 pa4 ma2 dib bw4 shadow-5"
                  src={p}
                />
              </Card>
            );
          })}
        </Row>
        <div className="center bb">
        { user && (
                      favorites.includes(params.id) ?
                      <div>
                        <f1 className= "code center f3">I am already in your favorites    </f1>
                      <FcLike className='start starFill f1 grow dim pointer' onClick={() =>{
                        deleteFavorite(params.id);
                      }}/>
                      </div>
                      :
                      <div>
                      <f1 className= "code center f3">add me to favorites     </f1>
                      <FcLikePlaceholder className='star starEmpty f1 grow dim pointer' onClick={() => {
                        addFavorite(params.id);
                      }}/>
                      </div>
                    )
                    }
        </div>
        <div class=" pa3 pa5-ns" style={{ margin: "auto", width: "40%" }}>
          <h4 class="f2 fw6">{pet.name || "None"}</h4>
          <br />
          <li className="f3 fw5 gray">
            Species: <i>{pet.species || "None"}</i>
          </li>
          <li className="f3 fw5 gray">
            Breed: <i>{pet.breed || "None"}</i>
          </li>
          <li className="f3 fw5 gray">
            Age: <i>{pet.age || "None"}</i>
          </li>
          <li className="f3 fw5 gray">
            Gender: <i>{pet.gender || "None"}</i>
          </li>
          <li className="f3 fw5 gray">
            Color: <i>{pet.color || "None"}</i>
          </li>
          <li className="f3 fw5 gray">
            Spayed/neutered:{" "}
            <i>{pet.spayed_or_neutered === true ? "Yes" : "No" || "None"}</i>
          </li>
          <li className="f3 fw5 gray">
            Vaccinations up to date:{" "}
            <i>
              {pet.vaccinations_up_to_date === true ? "Yes" : "No" || "None"}
            </i>
          </li>
          <li className="f3 fw5 gray">
            Location: <i>{pet.location || "None"}</i>
          </li>
        </div>
        <div className="f3 tc code">
          Interested? Connect with us.
          <br />
          <Link>adoption@pawstohands.org</Link>
        </div>
      </Container>
    </div>
  );
};

export default Pet;
