import React from "react";
import "./About.css";
const About = (props) => {
  return (
    <div className="about__container content-center">
      <section className="paragraph--section">
        <img
          className="centerImage   "
          src="/images/about.jpg"
          alt="cat"
          width="300px"
          heigh="300px"
        />
        <h1 className=" tc text-5xl font-bold about-title">
          About PawsToHands
        </h1>

        <div class="pa2" style={{ margin: "auto", width: "70%" }}>
          <blockquote className="athelas ml0 mt0 pl4 black-90 bl bw2 b--blue">
            <p className="f5 f4-m f3-l lh-copy  mt0">
              We are thinking about doing an animal adoption website. This
              project displays all animals that need a home and a new owner and
              provides the respectful data of these animals such as names, sex,
              age, breed, personality. 
            </p>
            <p className="f5 f4-m f3-l lh-copy  mt0">
              This project aims two target user groups. The first target user
              group will be the people who are looking for a place to adopt a
              new pet. The second target user group will be animal humane
              centers and shelters who needs a way of finding new owners for
              their animals.
            </p>
            <cite class="f6 ttu tracked fs-normal">―Paws To Hands</cite>
          </blockquote>
        </div>
        {/* <p className='tc code'>
                We are thinking about doing an animal adoption website. 
                This project displays all animals that need a home and a new owner and provides the respectful data of these animals such as names, sex, age, breed, personality. 
              </p>
              <p className='tc code'>
              This project aims two target user groups.

              The first target user group will be the people who are looking for a place to adopt a new pet.

              The second target user group will be animal humane centers and shelters who needs a way of finding new owners for their animals.
              </p> */}
      </section>
      {/* <section className="contributors-section">
              <h2 className=" code tc font-amatic text-5xl font-bold ">Contributors to be finished ...</h2>
            </section> */}
    </div>
  );
};

export default About;
