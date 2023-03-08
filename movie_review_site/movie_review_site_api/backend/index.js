import app from './server.js';
import mongodb from "mongodb";
import dotenv from "dotenv";
import MoviesDAO from './dao/moviesDAO.js';
import ReviewsDAO from './dao/reviewsDAO.js';
import FavoritesDAO from './dao/favoritesDAO.js';

async function main() {
	// set up the environment variables according to
	// .env file and write these variables in the 
	// process
	dotenv.config();
	// create a new mongodb client according to 
	// database url
	const client = new mongodb.MongoClient(
		process.env.MOVIEREVIEWS_DB_URI
	)
	// set port to process.env.PORT or 8000 default
	const port = process.env.PORT || 8000;
	try {
		// connect with mongoDB, if success, inject
		// client into moviesDAO
		await client.connect();
		await MoviesDAO.injectDB(client);
		await ReviewsDAO.injectDB(client);
		await FavoritesDAO.injectDB(client);
		// app listen to our port
		app.listen(port, () => {
			console.log('Server is running on port' + port);
		})
	} catch (e) {
		console.log(e);
		process.exit(1);
	}
}

main().catch(console.error);