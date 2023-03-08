import React, { useState, useEffect, useCallback } from "react";
import ShelterDataService from "../services/shelters";
import MenuItem from '@mui/material/MenuItem';
import Select from '@mui/material/Select';
import InputLabel from '@mui/material/InputLabel';
import FormControl  from '@mui/material/FormControl';
import Button from "react-bootstrap/Button";
import Row from "react-bootstrap/Row";
import "./Shelters.css";


const Shelters = (props) => {
  const [shelters, setShelters] = useState([]);
  const [searchName, setSearchName] = useState("");
  const [searchLocation, setSearchLocation] = useState("");

  const [locations, setLocations] = useState(["All Locations"]);
  const [currentPage, setCurrentPage] = useState(0);
  const [entriesPerPage, setEntriesPerPage] = useState(0);
  const [currentSearchMode, setCurrentSearchMode] = useState("");

  const retrieveLocations = useCallback(() => {
    ShelterDataService.getLocations()
      .then((response) => {
        setLocations(["All Locations"].concat(response.data));
      })
      .catch((e) => {
        console.log(e);
      });
  }, []);

  const retrieveShelters = useCallback(() => {
    setCurrentSearchMode("");
    ShelterDataService.getAll(currentPage)
      .then((response) => {
        setShelters(response.data.shelters);
        setCurrentPage(response.data.page);
        setEntriesPerPage(response.data.entries_per_page);
      })
      .catch((e) => {
        console.log(e);
      });
  }, [currentPage]);

  const find = useCallback(
    (query, by) => {
      ShelterDataService.find(query, by, currentPage)
        .then((response) => {
          //console.log(response.data);
          setShelters(response.data.shelters);
        })
        .catch((e) => {
          console.log(e);
        });
    },
    [currentPage]
  );

  const findByName = useCallback(() => {
    setCurrentSearchMode("findByName");
    find(searchName, "name");
  }, [find, searchName]);

  const findByLocation = useCallback(() => {
    setCurrentSearchMode("findByLocation");
    if (searchLocation === "All Locations") {
      retrieveShelters();
    } else {
      find(searchLocation, "location");
    }
  }, [find, searchLocation, retrieveShelters]);

  const retrieveNextPage = useCallback(() => {
    if (currentSearchMode === "findByName") {
      findByName();
    } else if (currentSearchMode === "findByLocation") {
      findByLocation();
    } else {
      retrieveShelters();
    }
  }, [currentSearchMode, findByName, findByLocation, retrieveShelters]);

  useEffect(() => {
    retrieveLocations();
  }, [retrieveLocations]);

  useEffect(() => {
    setCurrentPage(0);
  }, [currentSearchMode]);

  // Retrieve the next page if currentPage value changes
  useEffect(() => {
    retrieveNextPage();
  }, [currentPage, retrieveNextPage]);

  const onChangeSearchName = (e) => {
    const searchName = e.target.value;
    setSearchName(searchName);
  };

  const onChangeSearchLocation = (e) => {
    const searchLocation = e.target.value;
    setSearchLocation(searchLocation);
  };

  return (
    <div className="App">
      <div className="container mx-auto px-4 md:px-12 pt-6  ">
        <div className="mb-3 flex shelter-search-bar">
          <label className="location-search-label">Filter by place: </label>

          <FormControl className="location-selector" >
          <InputLabel id="demo-simple-select-label">Location</InputLabel>
          <Select 
              labelId="demo-simple-select-label"
              id="demo-simple-select"
              value={searchLocation}
              defaultValue={"All Locations"}
              label="Locations" 
              onChange={onChangeSearchLocation}>

            {locations.map((location, i) => {
              return (
                <MenuItem value={location} key={i}>
                  {location}
                </MenuItem>
              );
            })}



          </Select>
          </FormControl>
          <Button className="search-location-button"  onClick={findByLocation}>
          Search
        </Button>
        </div>
        

        <Row className="sheltersRow">
          {/* <div className="flex flex-wrap "> */}
          {shelters.map((shelter) => {
            return (
              <article class="center mw5 mw6-ns br3 hidden ba b--black-10 mv4">
                <h1 class="f4 bg-near-white br3 br--top black-60 mv0 pv2 ph3">
                  {shelter.name}
                </h1>
                <div class="pa3 bt b--black-10 sheltersListCard" 
                style={{backgroundImage: `url(${shelter.logo})`}}>
                
                  <li class="f6 f5-ns lh-copy measure">
                    Location:{shelter.location}
                  </li>
                  <li class="f6 f5-ns lh-copy measure">
                    Founded:{shelter.founded}
                  </li>
                 
                </div>
                <a class="link tc ph3 pv1 db bg-animate f6 br1 shelter-web-link" 
                href={shelter.website}
                target="_blank"
                rel="noreferrer">
                  More Information</a>
              </article>
            );
          })}
          {/* </div> */}
        </Row>
      </div>
    </div>
  );
};

export default Shelters;
