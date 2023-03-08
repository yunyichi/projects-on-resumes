import React, {useState, useEffect, useCallback } from 'react'
import { useNavigate, useParams, useLocation } from 'react-router-dom';
import UserDataService from "../services/user"


const Signin= ({loadUser}) => {
    const [password, setPassword] = useState("");
    const [email, setEmail] = useState("");
    const navigate = useNavigate();

    const onEmailChange = (event) => {
      setEmail(event.target.value)
    }

    const onPasswordChange = (event) => {
      setPassword(event.target.value)
    }

    const onSubmitSignin = () => {
      var data = {
        email: email,
        password: password
      }
      UserDataService.login(data)
        .then(response => {
          console.log(response.data.profile)
          loadUser(response.data.profile)
          navigate("/")
        })
        .catch(e =>{
          console.log(e);
          alert("Your information is not valid");
        })   
      }

    return (
        <div>
      <article className="br3 ba b--black-10 mv4 w-100 w-50-m w-25-l mw6 shadow-5 center">
        <main className="pa4 black-80">
          <div className="measure">
            <fieldset id="sign_up" className="ba b--transparent ph0 mh0">
              <legend className="f1 fw6 ph0 mh0">Sign In</legend>
              <div className="mt3">
                <label className="db fw6 lh-copy f6" htmlFor="email-address">Email</label>
                <input
                  className="pa2 input-reset ba bg-transparent hover-bg-black w-100"
                  type="email"
                  name="email-address"
                  id="email-address"
                  onChange={onEmailChange}
                />
              </div>
              <div className="mv3">
                <label className="db fw6 lh-copy f6" htmlFor="password">Password</label>
                <input
                  className="b pa2 input-reset ba bg-transparent hover-bg-black w-100"
                  type="password"
                  name="password"
                  id="password"
                  onChange={onPasswordChange}
                />
              </div>
            </fieldset>
            <div className="">
              <input
                onClick={onSubmitSignin}
                className="b ph3 pv2 input-reset ba b--black bg-transparent grow pointer f6 dib"
                type="submit"
                value="Sign in"
              />
            </div>
          </div>
        </main>
      </article>
      </div>
    );
  }

export default Signin;