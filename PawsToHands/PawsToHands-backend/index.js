import app from "./server.js";
import mongodb from "mongodb";
import dotenv from "dotenv";
import PetsDAO from "./dao/petsDAO.js";
import SheltersDAO from "./dao/sheltersDAO.js";
import userDAO from "./dao/userDAO.js";
import FavoritesDAO from './dao/favoritesDAO.js';

async function main() {
  dotenv.config();

  const client = new mongodb.MongoClient(process.env.PETS_DB_URI);
  const port = process.env.PORT || 8000;

  try {
    // Connect to MongoDB server
    await client.connect();
    await PetsDAO.injectDB(client);
    await SheltersDAO.injectDB(client);
    await userDAO.injectDB(client);
    await FavoritesDAO.injectDB(client);
    //await FavoritesDAO.injectDB(client);


    app.listen(port, () => {
      console.log("Server is running on port: " + port);
    });
  } catch (e) {
    console.error(e);
    process.exit(1);
  }
}

main().catch(console.error);