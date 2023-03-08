import SheltersDAO from "../dao/sheltersDAO.js";

export default class SheltersController {

   // For getting all shelters (broken into pages of 20 shelters per page)
   static async apiGetShelters(req, res, next) {
    const sheltersPerPage = req.query.sheltersPerPage
      ? parseInt(req.query.sheltersPerPage)
      : 20;
    const page = req.query.page ? parseInt(req.query.page) : 0;

    let filters = {};

    if (req.query.location) {
      filters.location = req.query.location;
    } else if (req.query.name) {
      filters.name = req.query.name;
    }


    const { sheltersList, totalNumShelters } = await SheltersDAO.getShelters({
      filters,
      page,
      sheltersPerPage,
    });

    let response = {
      shelters: sheltersList,
      page: page,
      filters: filters,
      entries_per_page: sheltersPerPage,
      total_results: totalNumShelters,
    };
    res.json(response);
  }



    // For getting a list of shelter locations we query the DAO again.
    static async apiGetLocations(req, res, next) {
      try {
        let propertyTypes = await SheltersDAO.getLocations();
        res.json(propertyTypes);
      } catch (e) {
        console.log(`API, ${e}`);
        res.status(500).json({ error: e });
      }
    }
}