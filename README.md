<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a id="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/parkertackley/apollo">
    <img src="img/arduino.png" alt="Logo" width="80">
  </a>

<h3 align="center">Apollo</h3>

  <p align="center">
    project_description
    <br />
    <a href="https://github.com/parkertackley/apollo"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/parkertackley/apollo">View Demo</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#parts">Parts List</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

The Apollo project is a device that can measure the force of ones throw by using a MPU6050 paired with other components to get the accelerometer readings on the Y-axis.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Parts
1. 1x Arduio UNO Rev3
2. 1x MPU6050
3. 1x I2C LCD
4. 1x RGB LED
5. 3x Buttons
6. 3x 220 Ohm Resistors
7. 1x Buzzer
8. Many wires

### Installation

1. Build Arduino with the given circuits and diagrams

1. Clone the repo
   ```sh
   git clone git@github.com:parkertackley/apollo.git
   ```
2. Install Arduino libraries
   ```sh
   MPU6050 by Electronic cats and LiquidCrystal I2C by Frank de BraBander
   ```
3. Connect Arduino with Components listed
   
4. Upload Sketch to Arduino

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

After setting up all the components and installing the required libraries, we are ready to start using Apollo.
To begin, upload the Arduino sketch to the connected Arduino. Once the sketch is uploaded, we will see the LCD turn on. After the initial setup period you will be greated with a screen that tells you to press button 2 to begin playing. The buttons are numbered 1-3 starting with the top most button, closest to the MPU6050, being button 1. 

Once pressed, you will be in the play state which will allow you to simulate a throw, without actually throwing the device of course. You will know you're in the play state because the RGB light will be lit up blue. You will have just over a second to "throw". The peak speed of your throw will be measured, recorded, and displayed on the LCD. Note: The high score will always be shown on the LCD after the first attempt.

After you have thrown, your score will be compared to the current top score. You will know that you've beat the high score by a flashing green light and a buzzing noise. If you haven't beaten a high score, you will see a yellow light.

Once you have seen your results, a red light will appear indicating that all readings have paused and you can safely give the device to another person or ready yourself to throw again. When you or the other player is ready, press the 2nd button which is the same button used to start the game, to begin the next turn. You can throw as many times as you'd like.

When you're ready to finish the throwing session or game you can press button 3, the bottom button, to end the game. You will be prompted with a game over screen and shown the high score of the session. To restart the game, simply press button 3 again when it prompts you to.

NOTE: At any point in the game you can press and hold button 1, the top button, to pause the game. No recording will happen and you can stay in this state for an indefinite amount of time.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: img/arduino.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
