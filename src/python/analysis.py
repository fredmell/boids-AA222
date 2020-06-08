import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

from pathlib import Path
from typing import Union

sns.set()
sns.set_style("whitegrid")

class Analyzer:
    def __init__(self, filename: Union[str, Path] = "../data/results.csv"):
        path = Path(filename)
        self.df = pd.read_csv(path)

    def plot_survival(self, show: bool = False) -> None:
        """ Plot the survival of prey boids.

        Args:
            show: Whether to display the generated figure.

        """
        fig, ax = plt.subplots(tight_layout=True)
        ax.plot(self.df["Generation"], self.df["Survivors"], label="Survivors")
        ax.plot(self.df["Generation"],
                self.df["Avg. survivors"],
                label="Rolling mean survivors")

        ax.set_ylabel("Normalized survivors")
        ax.set_xlabel("Generation")
        ax.set_xlim(
            (self.df["Generation"].iloc[0], self.df["Generation"].iloc[-1])
        )

        ax.legend()
        fig.savefig("../../latex/report/figures/survival.eps")

        if show:
            plt.show()

    def plot_coefficients(self, show: bool = False) -> None:
        """ Plot coefficient statistics of prey boids.

        Args:
            show: Whether to display the generated figure to screen.

        """
        fig, ax = plt.subplots(tight_layout=True)

        for abb, label in zip(("Sep", "Align", "Coh"), ("Separation", "Alignment", "Cohesion")):
            column_mean = "Avg. " + abb
            column_sd = "Sd. " + abb

            mean = self.df[column_mean]
            sd = self.df[column_sd]

            ax.plot(self.df["Generation"], mean, label=label)
            ax.fill_between(self.df["Generation"], mean + sd, mean - sd, alpha=0.3)

        ax.set_xlabel("Generation")
        ax.set_ylabel("Coefficient value")

        ax.set_xlim(
            (self.df["Generation"].iloc[0], self.df["Generation"].iloc[-1])
        )

        ax.legend()
        fig.savefig("../../latex/report/figures/coeffs.pdf")


if __name__ == '__main__':
    analyzer = Analyzer()
    analyzer.plot_survival()
    analyzer.plot_coefficients()
