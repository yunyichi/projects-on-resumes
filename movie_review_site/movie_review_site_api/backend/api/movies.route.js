import express from 'express';
import MoviesController from './movies.controller.js';
import ReviewsController from './reviews.controller.js';


// get access to express router
const router = express.Router();

router.route("/").get(MoviesController.apiGetMovies);
router.route("/id/:id").get(MoviesController.apiGetMovieById);
router.route("/ratings").get(MoviesController.apiGetRatings);

router.route("/review").post(ReviewsController.apiPostReview);
router.route("/review").put(ReviewsController.apiUpdateReview);
router.route("/review").delete(ReviewsController.apiDeleteReview);

router
    .route("/favorite")
    .put(FavoriteController.apiUpdateFavorites);
router
    .route("/favorites/:userId")
    .get(FavoriteController.apiGetFavorites);
export default router;