import mongodb from "mongodb";
import bcrypt from 'bcrypt'

const ObjectId = mongodb.ObjectId;

let user;

export default class userDAO {

  static async injectDB(conn) {
    if (user) {
      return;
    }
    try {
      user = await conn.db(process.env.PETS_NS).collection("user");
    } catch (e) {
      console.error(`Unable to connect in userDAO: ${e}`);
    }
  }


  static async register(email, name, password, date) {
    try {
        const exist = await user.findOne({
          email: email,
        });
        if (exist) {
          console.error("Unable to register");
          return { error};
        }
        const hash = await bcrypt.hash(password, 10);
        const reviewDoc = {
            name: name,
            email: email,
            hash: hash,
            date: date
        }
        // insertOne insert a document
        // return await user.insertOne(reviewDoc);
        await user.insertOne(reviewDoc);
        const profile = await user.findOne({
          email: email,
        });
        return profile
    } 
    catch(e) {
        console.error(`Unable to register: ${e}`);
        return { error: e};
    }  
}
static async login(email, password) {
  try {
    const profile = await user.findOne({
      email: email,
    });
    if (!profile) {
      console.error("Unable to find user");
      return { error};
    }
    const isValid = await bcrypt.compare(password, profile.hash);
    if (!isValid) {
      console.error("Unable to login, password is wrong");
      return { error};
    }
    return profile
  }
  catch(e) {
      console.error(`Unable to login: ${e}`);
      return { error: e};
  }  
}


}