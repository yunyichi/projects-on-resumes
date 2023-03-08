let petsCollection;


export default class PetsDAO {
  // connect to the database
  static async injectDB(conn) {
    if (petsCollection) {
      return;
    }
    try {
      petsCollection = await conn.db(process.env.PETS_NS).collection("pets");
    } catch (e) {
      console.error(`Unable to connect in PetsDAO: ${e}`);
    }
  }

  // get pets  todo
  static async getPets({ filters = null, page = 0, petsPerPage = 12 } = {}) {
    let query;
    if (filters) {
      if ("searchWords" in filters) {
        query = { $text: { $search: filters["searchWords"] } };
      } else if("species" in filters) {
        query = {"species" : { $eq : filters["species"] } };
      }
    }

    let cursor;
    try {
      cursor = await petsCollection
        .find(query)
        .limit(petsPerPage)
        .skip(petsPerPage * page);
      const petsList = await cursor.toArray();
      const totalNumPets = await petsCollection.countDocuments(query);
      return { petsList, totalNumPets };
    } catch (e) {
      console.error(`Unable to issue find command, ${e}`);
      return { petsList: [], totalNumPets: 0 };
    }
  }

  // get a single pet from petsCollection by its id
  static async getPetById(id) {
    try {
      const pet = await petsCollection.findOne({ _id: id });
      return pet;
    } catch (e) {
      console.error(`Something went wrong in getPetsById: ${e}`);
      throw e;
    }
  }

  // get a list of pets by a list of pets ids
  static async getPetsByIdList(arr) {
    let newArr = arr.map(function(val, index){
            return val;
        })

    try {
      let cursor = await petsCollection.find({
        _id: {
          $in: newArr
        }
      })
      const petsList = await cursor.toArray();
      return petsList;
    } catch (e) {
      console.error(`Unable to get By Id List, ${e}`);
      throw e;
    }
  }

  static async getPetsBySpecies(species) {
    let cursor;
    try {
      cursor = await petsCollection.find({ species:species});
      const pet = await cursor.toArray();
      return pet;
    } catch (e) {
      console.error(`Something went wrong in getPetsBySpecies: ${e}`);
      throw e;
    }
  }


  static async getSpecies() {
    let species = [];
    try {
      species = await petsCollection.distinct("species");
      return species;
    } catch (e) {
      console.error(`Unable to get species, ${e}`);
      return species;
    }
  }
}

