MakAir — Covid-19 Respirator
=====

**3D printable Covid-19 DIY respirator (caused by the SARS-CoV-2 virus). Aims at helping hospitals cope with a possible shortage of professional respirators during the outbreak.**

We are a distributed team of 50+ contributors, mostly spread through France. Makers, developers, university teachers, researchers and medical teams collaborated on this project. Our testing assembly operations are located in Nantes, France.

If you're new there, please read the explanations below. _Your contributions are much welcome!_

![MakAir Logo](./res/brand/logo-readme.png)

---

**⚠️ NOT READY YET, FURTHER INFORMATION WILL COME SHORTLY!**

---

**Shortcut links:**

* [General EN/FR docs on Google Docs](https://docs.google.com/document/d/1l1nt0o93kdfcmPygp1k6NYKrwIb_uN01kcBAfovy2dE/edit)
* [Regular video updates on YouTube](https://www.youtube.com/channel/UCcf_3KXjeJSMz39J6gsyTSg)

---

# Concept

Roughly, the idea is as follow: hospitals will soon lack mechanical artificial respirators. We aim at building a pump, and a valve system (controlled by electronics). This way, the breathing cycle can be enforced by proper air routing through the valve system.

The overall system is composed of sub-components that can be plugged together and wired to form an air circuit, namely:

- **Air pump** (called "Blower");
- **Air pump casing fit** (called "Blower Holder");
- **Valve system** (called "Pressure Valve");
- **Oxygen Mixer valve** (called "Oxygen Mixer");
- **Air filter casing (machine variant)** (called "Machine Filter Box"; 2 directions);
- **Air filter casing (patient variant)** (called "Patient Filter Box");
- **Connectors** (called "Pneumatic Connectors");
- **Housing container** (called "Box");

In order to ensure a proper breathing cycle (inhale + exhale), multiple valves need to be connected together to form a circuit. The motors needs to be controlled in harmony so that the air routing between each valve unit is consistent.

# Components

## Mechanics

| Component | Version | Last Changelog | Ready? | Live CAD Models | Contributors |
| --------- | ------- | -------------- | ------ | --------------- | ------------ |
| [Blower](./src/components/blower) | V13 | Increased air compression rate | ❌ | [view model](https://a360.co/2UsIdDU) | Gabriel Moneyron + [@baptistejamin](https://github.com/baptistejamin)
| [Blower Holder](./src/components/blower-holder) | V1 | Initial version | ✅ | none | Gabriel Moneyron + [@valeriansaliou](https://github.com/valeriansaliou)
| [Pressure Valve](./src/components/pressure-valve) | V3 | Improvements following durability tests | ✅ | none | Clément Niclot
| [Oxygen Mixer](./src/components/oxygen-mixer) | V5 | Adapted for internal piping system | ❌ | [view model](https://a360.co/3aG3pgK) | [@Melkaz](https://github.com/Melkaz)
| [Patient Filter Box](./src/components/patient-filter-box) | V5 | Update input/output mensurations | ❌ | none | Martial Medjber + [@eliottvincent](https://github.com/eliottvincent)
| [Machine Filter Box (Intake)](./src/components/machine-filter-box) | V1 | Wall-mountable, 3D-printability optimizations | ✅ | none | [@valeriansaliou](https://github.com/valeriansaliou)
| [Machine Filter Box (Outtake)](./src/components/machine-filter-box) | V1 | Wall-mountable, 3D-printability optimizations | ✅ | [view model](https://a360.co/2Utff87) | [@valeriansaliou](https://github.com/valeriansaliou)
| [Pneumatic Connectors](./src/components/pneumatic-connectors) | N/A | Initial version | ✅ | none | Gabriel Moneyron
| [Box](./src/components/box) | N/A | Initial design & fits | ❌ | none | Arthur Dagard

## Electronics

🚧 _(work in progress)_

## Software

🚧 _(work in progress)_

# Schemes

## Pneumatic Circuit Scheme

[![Pneumatic Circuit Scheme](./docs/Pneumatics/Pneumatic%20Circuit/Pneumatic%20Circuit.png)](./docs/Pneumatics/Pneumatic%20Circuit/Pneumatic%20Circuit.png)

_You may click on the scheme to enlarge._

## Pneumatic Circuit Drawing

[![Pneumatic Circuit Drawing](./docs/Pneumatics/Pneumatic%20Circuit/Pneumatics%20Drawing.jpg)](./docs/Pneumatics/Pneumatic%20Circuit/Pneumatics%20Drawing.jpg)

# News

## Live Updates

* Live updates on Telegram: [join channel](https://t.me/joinchat/AAAAAE_99-k7pKZur-GXCQ).

# Contact Us

Please [open an issue on GitHub](https://github.com/covid-response-projects/covid-respirator/issues/new) to contact us.

# Renders

## The "Pressure Valve"

🚧 _(work in progress)_

<p>
  <img alt="Pressure Valve Print" src="./src/components/pressure-valve/fdm/schemes/Pressure%20Valve%20(Print%201).jpg" height="240">
</p>

## The "Blower"

🎦 View: [Animation of the "Blower"](./src/components/blower/fdm/schemes/Blower%20(Animation%201).mp4)

<p>
  <img alt="Blower Render" src="./src/components/blower/fdm/schemes/Blower%20(Render%201).png" height="240">
</p>

## The "Blower Holder"

<p>
  <img alt="Blower Holder Render" src="./src/components/blower-holder/fdm/schemes/Blower%20Holder%20(Render%201).png" height="240">
  <img alt="Blower Holder Print" src="./src/components/blower-holder/fdm/schemes/Blower%20Holder%20(Print%201).jpg" height="240">
</p>

## The "Oxygen Mixer"

<p>
  <img alt="Oxygen Mixer Render" src="./src/components/oxygen-mixer/fdm/schemes/V5/Oxygen%20Mixer%20(Render%201).png" height="240">
  <img alt="Oxygen Mixer Print" src="./src/components/oxygen-mixer/fdm/schemes/V5/Oxygen%20Mixer%20(Print%201).jpg" height="240">
</p>

## The "Machine Filter Box"

<p>
  <img alt="Machine Filter Box Render" src="./src/components/machine-filter-box/fdm/schemes/V1/Filter%20Box%20(Render%201).png" height="320">
  <img alt="Machine Filter Box Print" src="./src/components/machine-filter-box/fdm/schemes/V1/Filter%20Box%20(Print%201).jpg" height="320">
</p>

## The "Patient Filter Box"

<p>
  <img alt="Patient Filter Box Render" src="./src/components/patient-filter-box/fdm/schemes/V4/Filter%20Box%20(Instructions).JPG" height="320">
  <img alt="Machine Filter Box Print" src="./src/components/patient-filter-box/fdm/schemes/V4/Filter%20Box%20(Print%201).jpg" height="320">
</p>

## The "Pneumatic Connectors"

<p>
  <img alt="Pneumatic Connector Blower Render" src="./src/components/pneumatic-connectors/fdm/schemes/Pneumatic%20Connector%20V1%20(Blower%20V4)/Pneumatic%20Connector%20Blower%20V4.png" height="240">
  <img alt="Pneumatic Connector O2 Render" src="./src/components/pneumatic-connectors/fdm/schemes/Pneumatic%20Connector%20V1%20(O2%20V3)/Pneumatic%20Connector%20O2%20V3.png" height="240">
  <img alt="Pneumatic Connector No pressure Render" src="./src/components/pneumatic-connectors/fdm/schemes/Pneumatic%20Connector%20V1%20(Respiratory%20:%20No%20pressure)/Pneumatic%20Connector%20Respiratory%20No%20pressure.png" height="240">
  <img alt="Pneumatic Connector No pressure Render" src="./src/components/pneumatic-connectors/fdm/schemes/Pneumatic%20Connector%20V1%20(Respiratory%20:%20Pressure)/Pneumatic%20Connector%20Respiratory%20Pressure.png" height="240">
  <img alt="Pneumatic Connector O2 Print" src="./src/components/pneumatic-connectors/fdm/schemes/Pneumatic%20Connector%20V1%20(O2%20V3)/Pneumatic%20Connector%20O2%20V3%20Print.jpg" height="240">
  <img alt="Pneumatic Connector Blower Print" src="./src/components/pneumatic-connectors/fdm/schemes/Pneumatic%20Connector%20V1%20(Blower%20V4)/Pneumatic%20Connector%20Blower%20V4%20Print.jpg" height="240">
  <img alt="Pneumatic Connector No pressure Print" src="./src/components/pneumatic-connectors/fdm/schemes/Pneumatic%20Connector%20V1%20(Respiratory%20:%20No%20pressure)/Pneumatic%20Connector%20Respiratory%20No%20pressure%20Print.jpg" height="240">
</p>

## The "Box"

<p>
  <img alt="Box Render" src="./src/components/box/acrylic/schemes/Box%20(Render201).png" height="240">
  <img alt="Box Render" src="./src/components/box/acrylic/schemes/Box%20(Render202).png" height="240">
  <img alt="Box Render" src="./src/components/box/acrylic/schemes/Box%20(Render203).png" height="240">
  <img alt="Box Render" src="./src/components/box/acrylic/schemes/Box%20(Render204).png" height="240">
  <img alt="Box Render" src="./src/components/box/acrylic/schemes/Box%20(Render205).png" height="240">
  <img alt="Box Render" src="./src/components/box/acrylic/schemes/Box%20(Render206).png" height="240">
  <img alt="Box Render" src="./src/components/box/acrylic/schemes/Box%20(Render207).png" height="240">
  <img alt="Box Render" src="./src/components/box/acrylic/schemes/Box%20(Render208).png" height="240">
</p>
