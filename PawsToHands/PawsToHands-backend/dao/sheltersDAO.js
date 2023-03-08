import mongodb from "mongodb";

const ObjectId = mongodb.ObjectId;

let shelters;

export default class SheltersDAO {

  static async injectDB(conn) {
    if (shelters) {
      return;
    }
    try {
      shelters = await conn.db(process.env.PETS_NS).collection("shelters");
    } catch (e) {
      console.error(`Unable to connect in SheltersDAO: ${e}`);
    }
  }



  static async getShelters({
    filters = null,
    page = 0,
    sheltersPerPage = 20,
  } = {}) {
    // empty object is default parameter in case arg is undefined
    let query;
    if (filters) {
      if ("name" in filters) {
        query = { $text: { $search: filters['name'] } };
      } else if ("location" in filters) {
        query = { "location": { $eq: filters['location'] } };
      }
    }
    let cursor;

    try {
      cursor = await shelters.find(query)
                           .limit(sheltersPerPage)
                           .skip(sheltersPerPage * page);

      const sheltersList = await cursor.toArray();
      const totalNumShelters = await shelters.countDocuments(query);
      return { sheltersList, totalNumShelters };
    } catch (e) {
      console.error(`Unable to issue find command, ${e}`);
      return { sheltersList: [], totalNumShelters: 0 };
    }
  }


  static async getLocations() {
    let locations = [];
    try {
      locations = await shelters.distinct("location");
      return locations;
    } catch (e) {
      console.error(`Unable to get locations, ${e}`);
      return locations;
    }
  }

}