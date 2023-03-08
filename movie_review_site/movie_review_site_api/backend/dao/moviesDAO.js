import mongodb from "mongodb";
const ObjectId = mongodb.ObjectId;

let movies;

export default class MoviesDAO {
	static async injectDB(conn) {
		if (movies) {
			return;
		}
		try {
			// movies is the collection we retrieved last week, it 
			// includes many tables, but it's not database, db -> collection -> tables
			movies = await conn.db(process.env.MOVIEREVIEWS_NS)
							.collection('movies');
		} catch (e) {
			console.error(`Unable to connect in MoviesDAO: ${e}`);
		}

	}
	static async getMovies({
		filters = null,
		page = 0,
		moviesPerPage = 20
	}={}) { // empty object is default parameter in case arg is undefined
		let query;
		// https://www.mongodb.com/docs/manual/reference/operator/query/text/
		if (filters) {
			// -----------not very clear why object can be writen like filter['title']---------
			if ("titie" in filters) {
				// $text performs a text search, $search searchs strings contain this key word
				query = { $text: { $search: filters['titie']}};
			} else if ("rated" in filters) {
				// find all items where rated === filters.rated
				query = {"rated": {$eq: filters['rated']}}
			}
		}

		let cursor;
		try {
			// the limit() function in MongoDB is used to 
			// specify the maximum number of results to be returned
			// Sometimes it is required to return a certain number 
			// of results after a certain number of documents. 
			// The skip() can do this job.
			// db.collection.find(query, projection, options)
			// all variables are optional
			// query Specifies selection filter, omit ({})
			// projection Specifies the fields to return in the 
			// documents that match the query filter. 
			// To return all fields in the matching documents, omit this parameter.
			// options Specifies additional options for the query. 
			// These options modify query behavior and how results are returned.
			cursor = await movies.find(query)
								 .limit(moviesPerPage)
								 .skip(moviesPerPage*page);
			// cursor.toArray() is a mongosh method, return an array of
			// all documents returned by the cursor
			const moviesList = await cursor.toArray();
			const totalNumMovies = await movies.countDocuments(query);
			return {moviesList, totalNumMovies};
		} catch(e) {
			console.errer(`Unable to issue find command, ${e}`);
			return {moviesList: [], totalNumMovies: 0};
		}

	}

	static async getRatings() {
		let ratings = [];
		try {
			// db.collection.distinct(field, query, options)
			// Finds the distinct values for a specified field 
			// across a single collection or view and returns the results in an array.
			ratings = await movies.distinct('rated');
			return ratings;
		} catch(e) {
			console.error(`Unable to get rating, ${e}`);
			return ratings;
		}

	}

	static async getMovieById(id) {
		// only write post review, no get review, because the way
		// to get review is searching the movie by Id.
		try {
			// An aggregation pipeline consists of 
			// one or more stages that process documents
			// https://www.mongodb.com/docs/manual/aggregation/
			// not only return the movie, but also the reviews
			// $lookup Performs a left outer join to a collection 
			// in the same database
			// from: collection to join, localField: field from the input documents
			// foreignField: field from the documents of the "from" collection
			// as: <output array field>
			// this is a movies collection, but if you want to search
			// for data in other collections within the same db, you can 
			// use $lookup:
			return await movies.aggregate([
				{
					$match: {
						// this id in db is ObjectId type
						_id: new ObjectId(id)
					}
				},
				{
					$lookup: {
						from: 'reviews',
						localField: '_id',
						foreignField: 'movie_id',
						as: 'reviews'
					}
				}
			]).next();
		} catch(e) {
			console.error(`Something went wrong in getMovieById: ${e}`);
			throw e;
		}
	}


}