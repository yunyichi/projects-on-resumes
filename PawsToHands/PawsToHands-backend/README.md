# Backend of PawsToHands

### Link to backend APIs:  
https://paws-to-hands-backend.herokuapp.com/

---
### Overview
* We have created a mongodb database `paws_to_hands_db`, which contains 4 collections.
* For `pets` and `shelters` collections, we have read operations.
* For `user` collection, we have create operations.
* For `favorite` collection, we have read and update operations.

<img width="800" alt="image" src="screenshots/database-collections.png">

---


## iter #3

## Task breakdown

Yunyi Chi
* Created 'user' collection in database, save user's login information.
* Added user route, user controller and userDAO for user authentication, Login and Register, encrypted user's password by bcrypt hashing.
* Finished favorite controller and favorite DAO.
<img width="800" alt="image" src="screenshots/iter3-paws-to-hands-user-collection.png">


Jiawei Liu

* Worked on favorite controller and favorite DAO.

Weixin Liu  

* Deployed to Heroku.

---
## iter #2


## Task breakdown


Weixin Liu  

* Created shelters collection in paws_to_hands_db.
<img width="800" alt="image" src="screenshots/iter2-paws-to-hands-collections.png">

* Implemented the backend, added routes and api and dao for getting shelters. 
<img width="800" alt="image" src="screenshots/iter2-paws-to-hands-backend-shelters-api.png">

* Deployed to Heroku.
---

## iter #1


## Task breakdown


Weixin Liu  

* Created paws_to_hands_db on Atlas.  
<img width="800" alt="image" src="screenshots/iter1-mongoDB-paws_to_hands_db.png">

* Implemented the backend, including getting routes, pets controller, and pets DAO.  
<img width="800" alt="image" src="screenshots/iter1-paws-to-hands-backend-api.png">

* Deployed to Heroku.

Yunyi Chi
* Added getPetsBySpecies function.




