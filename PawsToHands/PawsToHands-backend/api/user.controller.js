import userDAO from "../dao/userDAO.js";

export default class UserController {

    static async apiPostRegister(req, res, next){
		try {
			// console.log(req.body)
			const email = req.body.email;
			const name = req.body.name;
            const password = req.body.password;
			const date = new Date();
			const profile = await userDAO.register(
				email,
				name,
				password,
				date
			);
			var { error } = profile;
			if (error) {
				res.status(500).json({error: "Unable to post register information."});
			} else {
				console.log(profile)
				res.json({profile});
			}
		} 
		catch(e) {
			res.status(500).json({ error: e.message });		  
		}
	}
    static async apiPostLogin(req, res, next){
		try {
			// console.log(data)
			const email = req.body.email;
            const password = req.body.password;
			const profile = await userDAO.login(
				email,
				password,
			);
			var { error } = profile;
			if (error) {
				res.status(500).json({error: "Unable to get login information."});
			} else {
				res.json({profile});
			}
		} 
		catch(e) {
			res.status(500).json({ error: e.message });
		}
	}
}