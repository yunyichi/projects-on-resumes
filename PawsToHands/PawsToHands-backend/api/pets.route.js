import express from 'express';
import PetsController from './pets.controller.js';
import SheltersController from './shelters.controller.js';
import UserController from './user.controller.js';
import FavoritesController from './favorites.controller.js';

// import FavoritesController from './favorites.controller.js';

const router = express.Router();

router.route("/").get(PetsController.apiGetPets);

router.route("/id/:id").get(PetsController.apiGetPetById);


router.route("/species").get(PetsController.apiGetSpecies);

router.route("/species/:species").get(PetsController.apiGetPetsBySpecies);

router.route("/idList/:idList").get(PetsController.apiGetPetsByIdList);

router.route("/shelters").get(SheltersController.apiGetShelters);
router.route("/shelters/locations").get(SheltersController.apiGetLocations);

router.route("/register").post(UserController.apiPostRegister);
router.route("/login").post(UserController.apiPostLogin);

router
    .route("/favorites")
    .put(FavoritesController.apiUpdateFavorites);
router
    .route("/favorites/:userId")
    .get(FavoritesController.apiGetFavorites);
// router.route("/favorites").put(FavoritesController.apiUpdateFavorites);


export default router;