import PetsDAO from "../dao/petsDAO.js";

export default class PetsController {


  // For getting all pets (broken into pages of 12 pets per page)
  static async apiGetPets(req, res, next) {
    const petsPerPage = req.query.petsPerPage
      ? parseInt(req.query.petsPerPage)
      : 12;
    const page = req.query.page ? parseInt(req.query.page) : 0;


    let filters = {};
    if (req.query.species) {
      filters.species = req.query.species;
    } else if (req.query.searchWords) {
      filters.searchWords = req.query.searchWords;
    }

    const { petsList, totalNumPets } = await PetsDAO.getPets({
      filters,
      page,
      petsPerPage,
    });

    let response = {
      pets: petsList,
      page: page,
      filters: filters,
      entries_per_page: petsPerPage,
      total_results: totalNumPets,
    };
    res.json(response);


  }


  // For getting a single pet given its specific ID value.
  static async apiGetPetById(req, res, next) {
    try {
      let id = req.params.id || {};
      // console.log("id: " + id)
      let pet = await PetsDAO.getPetById(id);
      if (!pet) {
        res.status(404).json({ error: "not found" });
        return;
      }
      res.json(pet);
    } catch (e) {
      console.log(`API, ${e}`);
      res.status(500).json({ error: e });
    }
  }


  // For getting pets given a list of pets' ids
  static async apiGetPetsByIdList(req, res, next) {
    try {
      // console.log(req.params.idList)
      let arr = JSON.parse(req.params.idList);
      // console.log(arr)
      const petsList = await PetsDAO.getPetsByIdList(arr);
      res.json(petsList);
    } catch(e) {
      console.log(`API, ${e}`);
      res.status(500).json({error: e});
    }
  }

  // For getting a list of species we query the DAO again.
  static async apiGetSpecies(req, res, next) {
    try {
      let speciesList = await PetsDAO.getSpecies();
      res.json(speciesList);
    } catch (e) {
      console.log(`API, ${e}`);
      res.status(500).json({ error: e });
    }
  }
  static async apiGetPetsBySpecies(req, res, next) {
    try {
      let species = req.params.species || {};
      // console.log(species)
      let pet = await PetsDAO.getPetsBySpecies(species);
      if (!pet) {
        res.status(404).json({ error: "not found" });
        return;
      }
      res.json(pet);
    } catch (e) {
      console.log(`API, ${e}`);
      res.status(500).json({ error: e });
    }
  }

  
}
